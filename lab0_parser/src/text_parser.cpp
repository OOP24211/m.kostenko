#include <string>
#include <fstream>
#include "word_frequency.hpp"
#include "text_utils.hpp"

using namespace std;

char to_lower(char sym) {
    unsigned char uc = static_cast<unsigned char>(sym);

    if ('A' <= uc && uc <= 'Z') {
        return uc + 32;
    }
    if (192 <= uc && uc <= 223) {
        return uc + 32;
    }
    if (uc == 168) return 184;

    return uc;
}

bool is_letter(char sym) {
    unsigned char uc = static_cast<unsigned char>(sym);

    if ('A' <= uc && uc <= 'Z') return true;
    if ('a' <= uc && uc <= 'z') return true;
    if ((192 <= uc && uc <= 255) && uc != 215 && uc != 247) return true;
    if (uc == 168 || uc == 184) return true;

    return false;
}

class text_parser{
    
    private:

    string current_word;

    public:

    text_parser(){
        current_word = "";
    }
    void parse_from_input(istream& input, word_frequency_analyzer& analyzer){
        char c;
        while(input.get(c)){
            symbol_processing(c, analyzer);

        }
        finalize_current_word(analyzer);
    }

    void symbol_processing(char c, word_frequency_analyzer& analyzer){
        if(is_letter(c)){
            current_word+=to_lower(c);
        } else {
            if(!current_word.empty()){

                analyzer.add_word(current_word);
                current_word.clear();
            }
        }
    }
    void finalize_current_word(word_frequency_analyzer& analyzer){
        if(!current_word.empty()){
            analyzer.add_word(current_word);
            current_word.clear();
        }
    }
};