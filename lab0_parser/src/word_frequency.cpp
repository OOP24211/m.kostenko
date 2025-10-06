#include "word_frequency.hpp"
#include <algorithm>

using namespace std;

bool word_frequency_analyzer::compare_frequency(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

word_frequency_analyzer::word_frequency_analyzer() : total_words(0) {}

void word_frequency_analyzer::add_word(const string& current_word) {
    word_count[current_word]++;
    total_words++;
}

double word_frequency_analyzer::get_word_freq(int counter) const{
    if (total_words == 0) return 0.0;
    return (counter * 100.0) / total_words;
}

vector<pair<int, string>> word_frequency_analyzer::get_sorted_results() {
    sorted_by_freq.clear();

    for (const auto& pair : word_count) {
        sorted_by_freq.emplace_back(pair.second, pair.first);
    }

    // Используем std::sort вместо ручной сортировки
    sort(sorted_by_freq.begin(), sorted_by_freq.end(), compare_frequency);

    return sorted_by_freq;
}
