#pragma once
#include <string>
#include <map>
#include <vector>

class word_frequency_analyzer {
private:
    std::map<std::string, int> word_count;
    int total_words;
    std::vector<std::pair<int, std::string>> sorted_by_freq;

    static bool compare_frequency(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b);

public:
    word_frequency_analyzer();

    void add_word(const std::string& current_word);
    
    double get_word_freq(int counter) const;

    std::vector<std::pair<int, std::string>> get_sorted_results();
};
