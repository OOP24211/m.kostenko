#pragma once
#include <string>
#include <vector>

class ConfigParser {
public:
    explicit ConfigParser(const std::string& path);

    // список команд, каждая команда — список аргументов
    const std::vector<std::vector<std::string>>& commands() const;

private:
    std::vector<std::vector<std::string>> cmds;

    static std::vector<std::string> tokenize(const std::string& line);
};
