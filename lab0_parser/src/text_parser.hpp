#pragma once
#include <string>
#include <iostream>
#include "word_frequency.hpp"

class word_frequency_analyzer;

class text_parser {
private:
    std::string current_word;

    // Вспомогательные методы сделаны приватными
    bool is_letter(char c);
    char to_lower(char c);
    void symbol_processing(char c, word_frequency_analyzer& analyzer);
    void finalize_current_word(word_frequency_analyzer& analyzer);

public:
    text_parser();
    
    // Основной метод: парсит входной поток и заполняет анализатор
    void parse_from_input(std::istream& input, word_frequency_analyzer& analyzer);
};
