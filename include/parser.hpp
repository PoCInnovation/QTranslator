#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>

/**
 *  This namespace contains parsing functions used during transpilation
 */
namespace parser {

std::string create_variable(const std::vector<std::string> &line);
std::string operation_add(const std::vector<std::string> &line);
std::string operation_sub(const std::vector<std::string> &line);
std::string operation_print(const std::vector<std::string> &line);

/**
 *  Associative table that gives the size of a type as a string from a type as a string
 */
const std::map<std::string, std::string> type_size {
    {"char", std::to_string(sizeof(char))},
    {"int", std::to_string(sizeof(int))}
};

/**
 *  Associative table that redirects from a call as a string to a function
 */
const std::map<std::string, std::function<std::string(const std::vector<std::string> &)>> actions {
    {"char", create_variable},
    {"int", create_variable},
    {"add", operation_add},
    {"print", operation_print},
    {"sub", operation_sub},
};
}
