#include "WavReader.hpp"
#include "../exceptions/Exceptions.hpp"
#include <cstring>

WavReader::WavReader(const std::string& path) {
    file.open(path, std::ios::binary);
    if (!file) {
        throw WavFormatError("Cannot open WAV file: " + path);
    }

    char riffHeader[12];
    file.read(riffHeader, 12);
    
    if (file.gcount() != 12) {
        throw WavFormatError("Cannot read RIFF header");
    }
    
    if (std::memcmp(riffHeader, "RIFF", 4) != 0) {
        throw WavFormatError("Not a RIFF file");
    }
    
    if (std::memcmp(riffHeader + 8, "WAVE", 4) != 0) {
        throw WavFormatError("Not a WAVE file");
    }
    
    bool fmtFound = false;
    bool dataFound = false;
    
    while (true) {
        char chunkId[4];
        file.read(chunkId, 4);
        
        if (file.gcount() != 4) {
            break;
        }
        
        uint32_t chunkSize;
        file.read(reinterpret_cast<char*>(&chunkSize), 4);
        
        if (file.gcount() != 4) {
            break;
        }
        
        if (std::memcmp(chunkId, "fmt ", 4) == 0) {
            fmtFound = true;
            
            if (chunkSize < 16) {
                throw WavFormatError("Invalid fmt chunk size");
            }
            
            char fmtData[16];
            file.read(fmtData, 16);
            
            if (file.gcount() != 16) {
                throw WavFormatError("Cannot read fmt data");
            }
            
            uint16_t audioFormat = *reinterpret_cast<uint16_t*>(fmtData);
            uint16_t channels = *reinterpret_cast<uint16_t*>(fmtData + 2);
            uint32_t sampleRate = *reinterpret_cast<uint32_t*>(fmtData + 4);
            uint16_t bitsPerSample = *reinterpret_cast<uint16_t*>(fmtData + 14);
            
            if (audioFormat != 1) {
                throw WavFormatError("Only PCM format is supported");
            }
            if (channels != 1) {
                throw WavFormatError("Only mono (1 channel) is supported");
            }
            if (sampleRate != 44100) {
                throw WavFormatError("Only 44100 Hz sample rate is supported");
            }
            if (bitsPerSample != 16) {
                throw WavFormatError("Only 16-bit samples are supported");
            }
            
            if (chunkSize > 16) {
                file.seekg(chunkSize - 16, std::ios::cur);
            }
        }
        else if (std::memcmp(chunkId, "data", 4) == 0) {
            dataFound = true;
            dataRemaining = chunkSize;
            break;
        }
        else {
            file.seekg(chunkSize, std::ios::cur);
        }
    }
    
    if (!fmtFound) {
        throw WavFormatError("fmt chunk not found");
    }
    
    if (!dataFound) {
        throw WavFormatError("data chunk not found");
    }
}

bool WavReader::readSample(int16_t& sample) {
    if (dataRemaining < 2) {
        return false;
    }
    
    file.read(reinterpret_cast<char*>(&sample), 2);
    
    if (!file || file.gcount() != 2) {
        return false;
    }
    
    dataRemaining -= 2;
    return true;
}
