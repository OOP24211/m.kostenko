#pragma once
#include <fstream>
#include <cstdint>

class WavWriter {
public:
    explicit WavWriter(const std::string& path);
    void writeSample(int16_t sample);
    void finalize();
private:
    std::ofstream file;
    uint32_t dataSize = 0;
};
