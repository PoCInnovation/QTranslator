#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>

/**
 *  This namespace contains parsing functions used during transpilation
 */
namespace parser {

std::string action_new_tag(std::string tag_name, size_t line);

std::string action_ret(const std::vector<std::string> &line);

/**
 *  Associative table that redirects from a call as a string to a function
 */
const std::map<std::string, std::function<std::string(const std::vector<std::string> &)>> actions {
    {"ret", action_ret},
};
}
