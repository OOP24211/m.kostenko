#include "word_reader.hpp"
#include "text_utils.hpp"

#include <fstream>
#include <iostream>

void WordReader::readFromFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия входного файла\n";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::string currentWord;

        for (size_t i = 0; i < line.size(); ++i)
        {
            if (isLetterOrDigit(line[i]))
            {
                currentWord += line[i];
            }
            else
            {
                if (!currentWord.empty())
                {
                    words.push_back(normalizeWord(currentWord));
                    currentWord.clear();
                }
            }
        }

        if (!currentWord.empty())
            words.push_back(normalizeWord(currentWord));
    }

    file.close();
}

const std::list<std::string>& WordReader::getWords() const
{
    return words;
}
