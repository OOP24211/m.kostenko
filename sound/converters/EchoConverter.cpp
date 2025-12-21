#include "EchoConverter.hpp"

EchoConverter::EchoConverter(double delaySec, double d)
    : delay(static_cast<size_t>(delaySec * 44100)), decay(d),
      buffer(delay, 0) 
{
}

int16_t EchoConverter::process(int16_t in, size_t pos) {
    if (delay == 0) return in;
    
    size_t idx = pos % delay;
    
    double echo = buffer[idx] * decay;
    
    double mixed = in + echo;
    
    if (mixed > 32767) mixed = 32767;
    if (mixed < -32768) mixed = -32768;
    
    int16_t out = static_cast<int16_t>(mixed);
    
    buffer[idx] = out;
    
    return out;
}
