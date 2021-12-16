#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>

namespace parser {
std::string create_variable(const std::vector<std::string> &line);
std::string operation_add(const std::vector<std::string> &line);
std::string operation_sub(const std::vector<std::string> &line);

const std::map<std::string, std::string> types {
    {"char", std::to_string(sizeof(char))},
    {"int", std::to_string(sizeof(int))}
};

const std::map<std::string, std::function<std::string(const std::vector<std::string> &)>> actions {
    {"char", create_variable},
    {"int", create_variable},
    {"add", operation_add},
    {"sub", operation_sub}
};
}