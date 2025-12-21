#include "MuteConverter.hpp"

MuteConverter::MuteConverter(double f, double t)
    : from(f * 44100), to(t * 44100) {}

int16_t MuteConverter::process(int16_t in, size_t pos) {
    return (pos >= from && pos <= to) ? 0 : in;
}
