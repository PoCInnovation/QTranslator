#include <iostream>
#include <fstream>
#include "exception.hpp"
#include "format.hpp"
#include "tools.hpp"

namespace tools {
std::string get_file_content(const std::string &path)
{
    std::string file_content{};
    std::ifstream file_stream(path);
    if (!file_stream.is_open())
        throw transpiler::exception(0, format::bold, format::red, "error: ", format::reset, format::bold, "cannot open file '", path, '\'');
    std::getline(file_stream, file_content, '\0');
    return file_content;
}

std::vector<std::string> string_to_vector(const std::string &str, char separator, bool push_empty_strings)
{
    std::vector<std::string> array;
    std::string temp;
    size_t len = str.size();

    for (size_t i = 0; i < len; i++) {
        if (str[i] == separator) {
            if (push_empty_strings || !temp.empty()) {
                array.push_back(temp);
                temp.clear();
            }
        }
        else
            temp.push_back(str[i]);
    }
    if (push_empty_strings || !temp.empty())
        array.push_back(temp);
    return array;
}
}