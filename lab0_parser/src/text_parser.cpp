#include "text_parser.hpp"
#include "word_frequency.hpp"
#include "text_utils.hpp"

using namespace std;

text_parser::text_parser() {}

void text_parser::parse_from_input(istream& input, word_frequency_analyzer& analyzer) {
    char c;
    while(input.get(c)) {
        symbol_processing(c, analyzer);
    }
    finalize_current_word(analyzer);
}

void text_parser::symbol_processing(char c, word_frequency_analyzer& analyzer) {
    if(text_utils::is_letter(c)) {
        current_word += text_utils::to_lower(c);
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
