#ifndef WORD_READER_H
#define WORD_READER_H

#include <string>
#include <list>

class WordReader
{
private:
    std::list<std::string> words;

public:
    void readFromFile(const std::string& filename);
    const std::list<std::string>& getWords() const;
};

#endif
