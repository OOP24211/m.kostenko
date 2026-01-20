#pragma once

#include "../converters/Converter.hpp"  // Добавьте эту строку!
#include <string>
#include <vector>
#include <memory>

// Предварительные объявления (не нужны, т.к. мы включили заголовки)
// class Converter;  // Убрать - теперь есть #include "Converter.hpp"
class WavReader;
class WavWriter;

class Processor {
public:
    Processor(const std::string& configPath,
              const std::string& outputPath,
              const std::vector<std::string>& inputPaths);
    
    ~Processor();  // Явно объявите деструктор!

    void run();

private:
    std::string outputPath;
    std::vector<std::string> inputPaths;

    std::vector<std::unique_ptr<Converter>> converters;
    std::vector<std::unique_ptr<WavReader>> readers;

    void setupMixConverters();
};
