#pragma once

#include <memory>
#include <string>
#include <vector>

class Converter;


class ConverterFactory {
public:
    // создаёт конвертер по одной строке конфига
    static std::unique_ptr<Converter>
    create(const std::vector<std::string>& tokens);

    static void printHelp();
};
