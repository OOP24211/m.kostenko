#include <iostream>

#include "word_reader.hpp"
#include "word_frequency.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Использование:\n";
        std::cout << "word_count.exe input.txt output.csv\n";
        return 1;
    }

    WordReader reader;
    reader.readFromFile(argv[1]);

    FrequencyCounter counter;
    counter.count(reader.getWords());
    counter.writeCSV(argv[2]);

    std::cout << "Готово\n";
    return 0;
}
