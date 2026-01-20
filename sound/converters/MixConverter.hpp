#pragma once

#include "Converter.hpp"
#include <cstddef>

class WavReader;

class MixConverter : public Converter {
public:
    MixConverter(size_t streamIndex, double startSec);

    // Processor передаст reader, когда будет известен путь
    void setReader(WavReader* reader);

    int16_t process(int16_t in, size_t pos) override;

    const char* name() const override { return "mix"; }
    const char* help() const override {
        return "mix $n [start_sec] — mix with another input stream";
    }

    size_t getStreamIndex() const { return streamIndex; }

private:
    size_t streamIndex;     // номер входного файла (из $n)
    size_t startSample;     // позиция начала микса
    WavReader* reader;      // НЕ владеем!
};
