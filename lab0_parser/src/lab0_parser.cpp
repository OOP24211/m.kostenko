#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include "text_parser.hpp"
#include "word_frequency.hpp"


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 3) {
        std::cout << "ERROR: incorrect number of arguments" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cout << "Could not open the file!" << std::endl;
        return 1;
    }
    text_parser parser;
    word_frequency_analyzer analyzer;
    parser.parse_from_input(input_file, analyzer);
    std::vector<std::pair<int, std::string>> result_of_sort = analyzer.get_sorted_results();

    std::ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        std::cout << "Could not create output file!" << std::endl;
        return 1;
    }

    output_file << "Word,Count,Frequency" << std::endl;
    for (const auto& pair : result_of_sort) {
        std::string word = pair.second;
        int cnt = pair.first;
        double frequency = analyzer.get_word_freq(cnt);
        output_file << word << "," << cnt << "," << frequency << std::endl;
    }

    output_file.close();
    std::cout << "Analysis complete. Results saved to: " << argv[2] << std::endl;

    return 0;
}
