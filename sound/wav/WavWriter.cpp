#include "WavWriter.hpp"
#include <stdexcept>


WavWriter::WavWriter(const std::string& path) {
    file.open(path, std::ios::binary);

    char header[44] = {};
    file.write(header, 44); // заглушка
}

void WavWriter::writeSample(int16_t sample) {
    if (!file.write(reinterpret_cast<char*>(&sample), 2)) {
        throw std::runtime_error("Failed to write sample to output file");
    }
    dataSize += 2;
}

void WavWriter::finalize() {
    file.seekp(0);
    
    if (!file) {
        throw std::runtime_error("Output file stream is in bad state");
    }
    
    uint32_t chunkSize = 36 + dataSize;
    uint32_t subchunk1Size = 16;
    uint16_t audioFormat = 1;
    uint16_t channels = 1;
    uint32_t sampleRate = 44100;
    uint16_t bits = 16;
    uint32_t byteRate = sampleRate * 2;
    uint16_t blockAlign = 2;
    
    // Записываем заголовок
    file.write("RIFF", 4);
    file.write(reinterpret_cast<char*>(&chunkSize), 4);
    file.write("WAVE", 4);
    file.write("fmt ", 4);  
    file.write(reinterpret_cast<char*>(&subchunk1Size), 4);
    file.write(reinterpret_cast<char*>(&audioFormat), 2);
    file.write(reinterpret_cast<char*>(&channels), 2);
    file.write(reinterpret_cast<char*>(&sampleRate), 4);
    file.write(reinterpret_cast<char*>(&byteRate), 4);
    file.write(reinterpret_cast<char*>(&blockAlign), 2);
    file.write(reinterpret_cast<char*>(&bits), 2);
    file.write("data", 4);
    file.write(reinterpret_cast<char*>(&dataSize), 4);
    
    if (!file) {
        throw std::runtime_error("Failed to write WAV header");
    }
    
    file.close();
}
