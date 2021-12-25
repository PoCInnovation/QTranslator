#pragma once

#include <vector>
#include <string>

/**
 *  This namespace contains usefull tools to get and parse elements
 */
namespace tools {
    /**
     *  Get the content of a file as a string
     *
     *  @param path path to the file
     *  @return the file content as a string
     *  @throw transpiler::exception if the file is unreachable
     */
    std::string get_file_content(const std::string &path);
    /**
     *  Parse a string into a vector<string>
     *
     *  @param str the string to be parsed
     *  @param separator the character used to split the string
     *  @param push_empty_strings enable or disable the push of empty strings inside the vector
     *  @return the parsed string as an std::vector<string>
     */
    std::vector<std::string> string_to_vector(const std::string &str, char separator, bool push_empty_strings = false);
}