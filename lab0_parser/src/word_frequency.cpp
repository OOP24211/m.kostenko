#include <string>
#include <map>
#include<vector>

using namespace std;
#include "word_frequency.hpp"
#include <algorithm>

using namespace std;
using wfa = word_frequency_analyzer;  // alias

wfa::word_frequency_analyzer() : total_words(0) {}

void wfa::add_word(const string& current_word) {
    word_count[current_word]++;
    total_words++;
}

double wfa::get_word_freq(int counter) const {
    if (total_words == 0) return 0.0;
    return (counter * 100.0) / total_words;
}

bool wfa::compare_frequency(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

vector<pair<int, string>> wfa::get_sorted_results() {
    sorted_by_freq.clear();
    
    for (const auto& pair : word_count) {
        sorted_by_freq.emplace_back(pair.second, pair.first);
    }

    for (size_t i = 0; i < sorted_by_freq.size(); i++) {
        for (size_t j = i + 1; j < sorted_by_freq.size(); j++) {
            if (compare_frequency(sorted_by_freq[j], sorted_by_freq[i])) {
                swap(sorted_by_freq[i], sorted_by_freq[j]);
            }
        }
    }
    return sorted_by_freq;
}
