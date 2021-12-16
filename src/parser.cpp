#include "parser.hpp"
#include "exception.hpp"

namespace parser {

using string_pair = std::pair<std::string, std::string>;
std::vector<string_pair> symbol_table;

std::string create_variable(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw compiler::exception(line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](string_pair pair) {
        return pair.second == line[1];
    }) != std::end(symbol_table))
        throw compiler::exception(line.front(), "(...) redefinition of variable '", line[1], '\'');
    try {
        std::stoi(line[1]);
        throw compiler::exception(line.front(), "(...) expected unqualified-id as variable name");
    } catch (const compiler::exception &e) {
        throw compiler::exception(e.what());
    } catch (...) {}
    try {
        std::stoi(line[2]);
    } catch (...) {
        throw compiler::exception(line.front(), "(...) variable '", line[1], "' must be set to an integer value");
    }
    symbol_table.emplace_back(line[0], line[1]);
    return "qubit[" + parser::types.at(line[0]) + "] " + line[1] + ";";
}

std::string operation_add(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw compiler::exception(line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](string_pair pair) {
        return pair.second == line[1];
    }) == std::end(symbol_table))
        throw compiler::exception(line.front(), "(...) unknown symbol '", line[1], '\'');
    return "add;";
}

std::string operation_sub(const std::vector<std::string> &line)
{
    if (line.size() != 3)
        throw compiler::exception(line.front(), "(...) expected 2 arguments but ", std::to_string(line.size() - 1), " were provided");
    if (std::find_if(symbol_table.begin(), symbol_table.end(), [line](string_pair pair) {
        return pair.second == line[1];
    }) == std::end(symbol_table))
        throw compiler::exception(line.front(), "(...) unknown symbol '", line[1], '\'');
    return "sub;";
}
}