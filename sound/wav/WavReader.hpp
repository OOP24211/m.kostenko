#pragma once
#include <fstream>
#include <cstdint>
#include <cstring>

class WavReader {
public:
    explicit WavReader(const std::string& path);
    bool readSample(int16_t& sample);
    int sampleRate() const { return 44100; }
private:
    std::ifstream file;
    uint32_t dataRemaining;
};
