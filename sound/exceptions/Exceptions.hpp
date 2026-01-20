#pragma once
#include <exception>
#include <string>

class SoundException : public std::exception {
protected:
    std::string msg;
public:
    explicit SoundException(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class ArgError : public SoundException {
public: using SoundException::SoundException;
};

class WavFormatError : public SoundException {
public: using SoundException::SoundException;
};

class ConfigError : public SoundException {
public: using SoundException::SoundException;
};

class RuntimeError : public SoundException {
public: using SoundException::SoundException;
};
