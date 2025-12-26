#ifndef FREQUENCY_COUNTER_H
#define FREQUENCY_COUNTER_H

#include <map>
#include <list>
#include <string>

class FrequencyCounter
{
private:
    std::map<std::string, int> frequency;
    int totalWords;

public:
    FrequencyCounter();

    void count(const std::list<std::string>& words);
    void writeCSV(const std::string& filename);
};

#endif
