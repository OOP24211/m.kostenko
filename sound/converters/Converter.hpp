#pragma once
#include <cstdint>

class Converter {
public:
    virtual ~Converter() = default;
    virtual int16_t process(int16_t in, size_t pos) = 0;
    virtual const char* name() const = 0;
    virtual const char* help() const = 0;
};
