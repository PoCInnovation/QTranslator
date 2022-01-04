#include "parser.hpp"
#include <iostream>
#include <ostream>
#include "exception.hpp"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace parser {

using string_pair = std::pair<std::string, std::string>;
std::vector<string_pair> symbol_table;

std::string create_variable(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw transpiler::exception(0, line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
        return pair.second == line[1];
    }) != std::end(symbol_table))
        throw transpiler::exception(1, line.front(), "(...) redefinition of variable '", line[1], '\'');
    try {
        std::stoi(line[1]);
        throw transpiler::exception(1, line.front(), "(...) expected unqualified-id as variable name");
    } catch (const transpiler::exception &e) {
        throw transpiler::exception(1, e.what());
    } catch (...) {}
    try {
        std::stoi(line[2]);
    } catch (...) {
        throw transpiler::exception(2, line.front(), "(...) variable '", line[1], "' must be set to an integer value");
    }
    symbol_table.emplace_back(line[0], line[1]);
    return "qubit[" + parser::type_size.at(line[0]) + "] " + line[1] + ";";
}

void operation_parser(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw transpiler::exception(0, line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
        return pair.second == line[1];
    }) == std::end(symbol_table))
        throw transpiler::exception(1, line.front(), "(...) unknown symbol '", line[1], '\'');
    try {
        std::stoi(line[2]);
    } catch (...) {
        if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
            return pair.second == line[2];
        }) == std::end(symbol_table))
            throw transpiler::exception(2, line.front(), "(...) unknown symbol '", line[2], '\'');
    }
}

std::string operation_add(const std::vector<std::string> &line)
{
    operation_parser(line);
    std::string &variable_value = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
        return pair.second == line[1];
    })->first;

    int result = system((std::string("python ./calculator/calculator.py ADD ") + variable_value + " " + line[2]).c_str());

    variable_value = std::to_string(std::stoi(variable_value) + result);

    return "";
}

std::string operation_sub(const std::vector<std::string> &line)
{
    operation_parser(line);
    std::string &variable_value = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
        return pair.second == line[1];
    })->first;

    int result = system((std::string("python ./calculator/calculator.py SUB ") + variable_value + " " + line[2]).c_str());

    variable_value = std::to_string(std::stoi(variable_value) + result);

    return "";
}

std::string operation_print(const std::vector<std::string> &line)
{
    std::string variable_value = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const string_pair &pair) {
        return pair.second == line[1];
    })->second;

    std::cout << variable_value << std::endl;
    return "";
}
}
