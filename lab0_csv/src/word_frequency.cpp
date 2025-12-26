#include "word_frequency.hpp"

#include <fstream>
#include <iostream>

FrequencyCounter::FrequencyCounter()
{
    totalWords = 0;
}

void FrequencyCounter::count(const std::list<std::string>& words)
{
    for (std::list<std::string>::const_iterator it = words.begin();
         it != words.end(); ++it)
    {
        frequency[*it]++;
        totalWords++;
    }
}

void FrequencyCounter::writeCSV(const std::string& filename)
{
    std::ofstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия CSV файла\n";
        return;
    }

    std::list<std::pair<std::string, int>> sorted;
    for (std::map<std::string, int>::iterator it = frequency.begin();
         it != frequency.end(); ++it)
    {
        sorted.push_back(*it);
    }

    sorted.sort([](const std::pair<std::string, int>& a,
                   const std::pair<std::string, int>& b)
    {
        return a.second > b.second;
    });

    file << "Word,Frequency,Frequency(%)\n";

    for (std::list<std::pair<std::string, int>>::iterator it = sorted.begin();
         it != sorted.end(); ++it)
    {
        double percent = 0.0;
        if (totalWords != 0)
            percent = (double)it->second * 100.0 / totalWords;

        file << it->first << ","
             << it->second << ","
             << percent << "\n";
    }

    file.close();
}
