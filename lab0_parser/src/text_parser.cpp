#include <string>
#include "word_frequency.hpp"
#include "text_parser.hpp"



text_parser::text_parser() : current_word("") {}

void text_parser::parse_from_input(std::istream& input, word_frequency_analyzer& analyzer) {
    char c;
    while(input.get(c)) {
        symbol_processing(c, analyzer);
    }
    finalize_current_word(analyzer);
}


bool              text_parser::is_letter(char c) {
    unsigned char uc = static_cast<unsigned char>(c);

    if ('A' <= uc && uc <= 'Z') return true;
    if ('a' <= uc && uc <= 'z') return true;
    if ((192 <= uc && uc <= 255) && uc != 215 && uc != 247) return true;
    if (uc == 168 || uc == 184) return true;

    return false;
}

char text_parser::to_lower(char c) {
    const unsigned char uc = static_cast<unsigned char>(c);

    if ('A' <= uc && uc <= 'Z') {
        return uc + 32;
    }
    if (192 <= uc && uc <= 223) {
        return uc + 32;
    }
    if (uc == 168) return static_cast<char>(184);

    return uc;
}

void text_parser::symbol_processing(char c, word_frequency_analyzer& analyzer) {
    if(is_letter(c)) {
        current_word += to_lower(c);
    } else {
        if(!current_word.empty()) {
            analyzer.add_word(current_word);
            current_word.clear();
        }
    }
}

void text_parser::finalize_current_word(word_frequency_analyzer& analyzer) {
    if(!current_word.empty()) {
        analyzer.add_word(current_word);
        current_word.clear();
    }
}
