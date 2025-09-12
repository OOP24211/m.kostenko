#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <locale>
using namespace std;

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

int calculate_total_words(const map<string, int>& word_map) {
    int total = 0;
    for (const auto& pair : word_map) {
        total += pair.second;
    }
    return total;
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

    map<string, int> word_count;
    string current_word;
    char c;

    while (input_file.get(c)) {
        if (is_letter(c)) {
            current_word += to_lower(c); // Передаем char, а не char*
        }
        else {
            if (!current_word.empty()) {
                word_count[current_word]++;
                current_word.clear();
            }
        }
    }

    if (!current_word.empty()) {
        word_count[current_word]++;
    }

    int total_word_count = calculate_total_words(word_count);
    vector<pair<int, string>> sorted;

    for (const auto& pair : word_count) {
        sorted.emplace_back(pair.second, pair.first);
    }

    // Сортировка
    for (size_t i = 0; i < sorted.size(); i++) {
        for (size_t j = i + 1; j < sorted.size(); j++) {
            if (compare_frequency(sorted[j], sorted[i])) {
                swap(sorted[i], sorted[j]);
            }
        }
    }

    ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cout << "Could not create output file!" << endl;
        return 1;
    }

    output_file << "Word,Count,Frequency" << endl;
    for (const auto& pair : sorted) {
        string word = pair.second;      // Само слово
        int cnt = pair.first;           // Количество
        double frequency = (cnt * 100.0) / total_word_count;
        output_file << word << "," << cnt << "," << frequency << endl;
    }

    output_file.close();
    cout << "Analysis complete. Results saved to: " << argv[2] << endl;

    return 0;
}