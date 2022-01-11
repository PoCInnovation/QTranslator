#include <variant>
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

struct symbol_data {
    std::string type{};
    int value;
};

using symbol_pair = std::pair<std::string, symbol_data>;
std::vector<symbol_pair> symbol_table;

struct operation_data {
    int arg1, arg2;
    std::vector<symbol_pair>::iterator result;
};

std::string create_variable(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw transpiler::exception(0, line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
        return pair.first == line[1];
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
    symbol_table.push_back(symbol_pair(line[1], {line[0], std::stoi(line[2])}));
    return "qubit[" + parser::type_size.at(line[0]) + "] " + line[1] + ";";
}

operation_data operation_parser(const std::vector<std::string> &line)
{
    int arg1;
    int arg2;

    if (line.size() != 3)
        throw transpiler::exception(0, line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
        return pair.first == line[1];
    }) == std::end(symbol_table))
        throw transpiler::exception(1, line.front(), "(...) unknown symbol '", line[1], '\'');
    try {
        std::stoi(line[2]);
    } catch (...) {
        if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
            return pair.first == line[2];
        }) == std::end(symbol_table))
            throw transpiler::exception(2, line.front(), "(...) unknown symbol '", line[2], '\'');
    }
    
    auto it1 = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
        return pair.first == line[1];
    });
    if (it1 != std::end(symbol_table)) {
        arg1 = it1->second.value;
    } else {
        throw transpiler::exception(1, line.front(), "(...) unknown symbol '", line[1], '\'');
    }

    auto it2 = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
        return pair.first == line[2];
    });
    if (it2 != std::end(symbol_table)) {
        arg2 = it2->second.value;
    } else {
        try {
            arg2 = std::stoi(line[2]);
        } catch (...) {
            throw transpiler::exception(2, line.front(), "(...) unknown symbol '", line[2], '\'');
        }
    }
    return {arg1, arg2, it1};
}

int exec(const std::string &cmd) {
    std::array<char, 128> buffer;
    std::string result;
    #if defined(_WIN32)
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
    #else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    #endif
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
        result += buffer.data();
    return std::stoi(result);
}

std::string operation_add(const std::vector<std::string> &line)
{
    auto args = operation_parser(line);
    
    int result = exec((std::string("python ./calculator/calculator.py ADD ") + std::to_string(args.arg1) + " " + std::to_string(args.arg2) + " ibm"));
    args.result->second.value = result;

    return "";
}

std::string operation_sub(const std::vector<std::string> &line)
{
    auto args = operation_parser(line);
    
    int result = exec((std::string("python ./calculator/calculator.py SUB ") + std::to_string(args.arg1) + " " + std::to_string(args.arg2) + " ibm"));
    args.result->second.value = result;

    return "";
}

std::string operation_print(const std::vector<std::string> &line)
{
    auto it = std::find_if(symbol_table.begin(), symbol_table.end(), [line](const symbol_pair &pair) {
        return pair.first == line[1];
    });
    if (it != std::end(symbol_table)) {
        std::cout << it->second.value << std::endl;
    }

    return "";
}
}
