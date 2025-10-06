#include "text_utils.hpp"

namespace text_utils {
    char to_lower(char sym) {
        const unsigned char uc = static_cast<unsigned char>(sym);
        if ('A' <= uc && uc <= 'Z') return uc + 32;
        if (192 <= uc && uc <= 223) return uc + 32;
        if (uc == 168) return 184;
        return uc;
    }

    bool is_letter(char sym) {
        const unsigned char uc = static_cast<unsigned char>(sym);
        if ('A' <= uc && uc <= 'Z') return true;
        if ('a' <= uc && uc <= 'z') return true;
        if ((192 <= uc && uc <= 255) && uc != 215 && uc != 247) return true;
        if (uc == 168 || uc == 184) return true;
        return false;
    }
}
