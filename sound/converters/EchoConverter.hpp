#pragma once
#include "Converter.hpp"
#include <vector>

class EchoConverter : public Converter {
    size_t delay;  
    std::vector<int16_t> buffer;
    double decay;
public:
    EchoConverter(double delaySec, double d);
    int16_t process(int16_t in, size_t pos) override;
    const char* name() const override { return "echo"; }
    const char* help() const override {
        return "echo <delay_sec> <decay> — add echo effect";
    }
};
