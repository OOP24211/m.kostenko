#include "ConfigParser.hpp"
#include "../exceptions/Exceptions.hpp"
#include <fstream>
#include <sstream>
#include <cctype>

ConfigParser::ConfigParser(const std::string& path) {
    std::ifstream file(path);
    if (!file)
        throw ConfigError("Cannot open config file: " + path);

    std::string line;
    size_t lineNum = 0;

    while (std::getline(file, line)) {
        ++lineNum;

        // убираем пробелы в начале
        size_t pos = line.find_first_not_of(" \t");
        if (pos == std::string::npos)
            continue;

        if (line[pos] == '#')
            continue;

        auto tokens = tokenize(line);

        if (tokens.empty())
            continue;

        if (tokens[0].empty())
            throw ConfigError("Empty command at line " + std::to_string(lineNum));

        cmds.push_back(tokens);
    }

    if (cmds.empty())
        throw ConfigError("Config file contains no commands");
}

const std::vector<std::vector<std::string>>&
ConfigParser::commands() const {
    return cmds;
}

std::vector<std::string>
ConfigParser::tokenize(const std::string& line) {
    std::vector<std::string> result;
    std::istringstream iss(line);
    std::string token;

    while (iss >> token) {
        
        if (token[0] == '$') {
            if (token.size() == 1)
                throw ConfigError("Invalid stream reference '$'");

            for (size_t i = 1; i < token.size(); ++i) {
                if (!std::isdigit(token[i]))
                    throw ConfigError("Invalid stream reference: " + token);
            }
        }
        result.push_back(token);
    }

    return result;
}
