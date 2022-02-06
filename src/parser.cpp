#include "parser.hpp"
#include "exception.hpp"

namespace parser {

std::map<std::string, size_t> tags_table;

std::string action_new_tag(std::string tag_name, size_t line)
{
    tag_name.pop_back();
    if (tags_table.contains(tag_name))
        throw transpiler::exception(0, "multiple definition of tag ", tag_name, ". It was alredy created line ", tags_table[tag_name]);
    tags_table[tag_name] = line;
    return tag_name + ":";
}

std::string action_ret(const std::vector<std::string> &line)
{
    if (line.size() != 1)
        throw transpiler::exception(1, line.front(), "(...) expected no arguments but ", std::to_string(line.size() - 1), " were provided");
    return "return";
}
}
