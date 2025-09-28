#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <locale>
#include "text_parser.hpp"
#include "word_frequency.hpp"

using namespace std;


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