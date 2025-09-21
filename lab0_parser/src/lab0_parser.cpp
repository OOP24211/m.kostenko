#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <locale>
using namespace std;

class word_frequency_analyzer{
    
    private:
    map<string,int>word_count;       // Хранит слова и их количество
    int total_words;                 // Общее количество всех слов
    vector<pair<int,string>> sorted_by_freq; // Слова, отсортированные по частоте
    
    public:
    word_frequency_analyzer(){
        total_words = 0;
    }

    void add_word(string& current_word){
        word_count[current_word]++;
        total_words++;
    }

    double get_word_freq(int counter){
        double frequency =(counter*100.0)/total_words;
        return frequency;
    }
        vector<pair<int,string>> get_sorted_results(){
        
        for (const auto& pair : word_count) {
        sorted_by_freq.emplace_back(pair.second, pair.first);
        }

        // Сортировка
        for (size_t i = 0; i < sorted_by_freq.size(); i++) {
            for (size_t j = i + 1; j < sorted_by_freq.size(); j++) {
                if (compare_frequency(sorted_by_freq[j], sorted_by_freq[i])) {
                    swap(sorted_by_freq[i], sorted_by_freq[j]);
                }
            }
        }
        return sorted_by_freq;
    }


};

class text_parser{
    
    private:

    string current_word;

    public:

    text_parser(){
        current_word = "";
    }
    // Основной метод: парсит входной поток и заполняет анализатор
    void parse_from_input(istream& input, word_frequency_analyzer& analyzer){
        char c;
        while(input.get(c)){
            symbol_processing(c, analyzer);

        }
        finalize_current_word(analyzer);
    }
    // Обрабатывает один символ: добавляет к слову или завершает слово
    void symbol_processing(char c, word_frequency_analyzer analyzer){
        if(is_letter(c)){
            current_word+=to_lower(c);
        } else {
            if(!current_word.empty()){

                analyzer.add_word(current_word);
                current_word.clear();
            }
        }
    }
    void finalize_current_word(word_frequency_analyzer analyzer){
        if(!current_word.empty()){
            analyzer.add_word(current_word);
            current_word.clear();
        }
    }

};

bool compare_frequency(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

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

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 3) {
        cout << "ERROR: incorrect number of arguments" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cout << "Could not open the file!" << endl;
        return 1;
    }
    text_parser parser;
    word_frequency_analyzer analyzer;
    parser.parse_from_input(input_file, analyzer);
    vector<pair<int, string>> result_of_sort = analyzer.get_sorted_results();

    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cout << "Could not create output file!" << endl;
        return 1;
    }

    output_file << "Word,Count,Frequency" << endl;
    for (const auto& pair : result_of_sort) {
        string word = pair.second;      // Само слово
        int cnt = pair.first;           // Количество
        double frequency = analyzer.get_word_freq(cnt);
        output_file << word << "," << cnt << "," << frequency << endl;
    }

    output_file.close();
    cout << "Analysis complete. Results saved to: " << argv[2] << endl;

    return 0;
}