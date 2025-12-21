#include "Processor.hpp"
#include "../config/ConfigParser.hpp"
#include "../converters/ConverterFactory.hpp"
#include "../converters/MixConverter.hpp"
#include "../wav/WavReader.hpp"
#include "../wav/WavWriter.hpp"
#include "../exceptions/Exceptions.hpp"

Processor::Processor(const std::string& configPath,
                     const std::string& outPath,
                     const std::vector<std::string>& inputs)
    : outputPath(outPath), inputPaths(inputs)
{
    if (inputPaths.empty()) {
        throw ArgError("No input files specified");
    }

    // читаем конфиг
    ConfigParser parser(configPath);

    // создаём конвертеры через фабрику
    for (const auto& cmd : parser.commands()) {
        converters.push_back(ConverterFactory::create(cmd));
    }

    // создаём ридеры для всех входных файлов
    for (const auto& path : inputPaths) {
        readers.push_back(std::make_unique<WavReader>(path));
    }

    setupMixConverters();
}

Processor::~Processor() = default;

void Processor::run() {
    if (readers.empty()) {
        throw RuntimeError("No readers initialized");
    }

    WavWriter writer(outputPath);
    
    size_t samplePos = 0;
    int16_t sample;
    
    // читаем сэмплы из основного потока
    while (readers[0]->readSample(sample)) {
        int16_t processedSample = sample;
        
        // применяем все конвертеры по очереди
        for (auto& converter : converters) {
            processedSample = converter->process(processedSample, samplePos);
        }
        
        // записываем обработанный сэмпл
        writer.writeSample(processedSample);
        ++samplePos;
    }
    
    writer.finalize();
}

void Processor::setupMixConverters() {
    for (auto& converter : converters) {
        auto* mixConverter = dynamic_cast<MixConverter*>(converter.get());
        
        if (mixConverter) {
            size_t streamIndex = mixConverter->getStreamIndex();
            
            if (streamIndex == 0 || streamIndex > readers.size()) {
                throw RuntimeError("Invalid stream index in mix converter: " + 
                                  std::to_string(streamIndex));
            }
            
            mixConverter->setReader(readers[streamIndex - 1].get());
        }
    }
}
