// MuteConverter.h
#pragma once
#include "Converter.hpp"

class MuteConverter : public Converter {
    size_t from, to;
public:
    MuteConverter(double f, double t);
    int16_t process(int16_t in, size_t pos) override;
    const char* name() const override { return "mute"; }
    const char* help() const override {
        return "mute <start_sec> <end_sec> — silence interval";
    }
};
