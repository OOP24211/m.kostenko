#include "text_utils.hpp"

bool isLetterOrDigit(char c)
{
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}

char toLowerChar(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

std::string normalizeWord(const std::string& word)
{
    std::string result;
    for (size_t i = 0; i < word.size(); ++i)
        result += toLowerChar(word[i]);
    return result;
}
