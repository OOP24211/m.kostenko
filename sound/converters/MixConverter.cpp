#include "MixConverter.hpp"
#include "../wav/WavReader.hpp"

MixConverter::MixConverter(size_t index, double startSec)
    : streamIndex(index),
      startSample(static_cast<size_t>(startSec * 44100)),
      reader(nullptr) {}

void MixConverter::setReader(WavReader* r) {
    reader = r;
}

int16_t MixConverter::process(int16_t in, size_t pos) {
    if (!reader || pos < startSample)
        return in;

    int16_t s;
    if (!reader->readSample(s))
        return in;

    return static_cast<int16_t>((in + s) / 2);
}
