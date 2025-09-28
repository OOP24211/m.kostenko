#include <string>
#include <map>
#include<vector>

using namespace std;

bool compare_frequency(const pair<int, string>& a, const pair<int, string>& b) {
    return a.first > b.first;
}

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

	double get_word_freq(int counter) const {
    	if (total_words == 0) return 0.0;
    	return (counter * 100.0) / total_words;
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