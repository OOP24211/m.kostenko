#include "ConverterFactory.hpp"

#include "Converter.hpp"
#include "MuteConverter.hpp"
#include "MixConverter.hpp"
#include "EchoConverter.hpp"

#include "../exceptions/Exceptions.hpp"

#include <iostream>
#include <cstdlib>
namespace {

double parseDouble(const std::string& s) {
    try {
        size_t pos;
        double v = std::stod(s, &pos);
        if (pos != s.size())
            throw ConfigError("Invalid number: " + s);
        return v;
    } catch (...) {
        throw ConfigError("Invalid number: " + s);
    }
}

size_t parseStreamIndex(const std::string& s) {
    if (s.size() < 2 || s[0] != '$')
        throw ConfigError("Expected stream reference like $2, got: " + s);

    for (size_t i = 1; i < s.size(); ++i)
        if (!isdigit(s[i]))
            throw ConfigError("Invalid stream reference: " + s);

    size_t idx = std::stoul(s.substr(1));
    if (idx == 0)
        throw ConfigError("Stream index must be >= 1");

    return idx;
}

}
std::unique_ptr<Converter>
ConverterFactory::create(const std::vector<std::string>& tokens) {
    if (tokens.empty())
        throw ConfigError("Empty converter command");

    const std::string& name = tokens[0];

    // ===== mute =====
    if (name == "mute") {
        if (tokens.size() != 3)
            throw ConfigError("mute syntax: mute <start_sec> <end_sec>");

        double start = parseDouble(tokens[1]);
        double end   = parseDouble(tokens[2]);

        if (start < 0 || end < 0 || end < start)
            throw ConfigError("Invalid mute interval");

        return std::make_unique<MuteConverter>(start, end);
    }

    // ===== mix =====
    if (name == "mix") {
        if (tokens.size() != 2 && tokens.size() != 3)
            throw ConfigError("mix syntax: mix $n [start_sec]");

        size_t streamIndex = parseStreamIndex(tokens[1]);

        double start = 0.0;
        if (tokens.size() == 3)
            start = parseDouble(tokens[2]);

        return std::make_unique<MixConverter>(streamIndex, start);
    }

    // ===== echo =====
    if (name == "echo") {
        if (tokens.size() != 3)
            throw ConfigError("echo syntax: echo <delay_sec> <decay>");

        double delay = parseDouble(tokens[1]);
        double decay = parseDouble(tokens[2]);

        if (delay <= 0)
            throw ConfigError("Echo delay must be > 0");

        if (decay <= 0 || decay >= 1)
            throw ConfigError("Echo decay must be in (0, 1)");

        return std::make_unique<EchoConverter>(delay, decay);
    }

    throw ConfigError("Unknown converter: " + name);
}
void ConverterFactory::printHelp() {
    std::cout << "Sound Processor\n\n";
    std::cout << "Usage:\n";
    std::cout << "  sound_processor -c <config.txt> <output.wav> "
                 "<input1.wav> [input2.wav ...]\n";
    std::cout << "  sound_processor -h\n\n";

    std::cout << "Supported converters:\n\n";

    {
        MuteConverter c(0, 1);
        std::cout << "  " << c.name() << "\n"
                  << "    " << c.help() << "\n\n";
    }
    {
        MixConverter c(1, 0);
        std::cout << "  " << c.name() << "\n"
                  << "    " << c.help() << "\n\n";
    }
    {
        EchoConverter c(0.3, 0.5);
        std::cout << "  " << c.name() << "\n"
                  << "    " << c.help() << "\n\n";
    }

    std::cout << "Config file rules:\n";
    std::cout << "  • One converter per line\n";
    std::cout << "  • Arguments separated by spaces\n";
    std::cout << "  • Lines starting with # are comments\n\n";

    std::cout << "Example config:\n";
    std::cout << "  mute 0 30\n";
    std::cout << "  mix $2 10\n";
    std::cout << "  echo 0.4 0.6\n";
}
