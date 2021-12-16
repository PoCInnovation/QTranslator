#pragma once

#include <vector>
#include <string>

class qtranslator
{
private:
    std::string m_in = "";
    std::string m_out = "out.qasm";
    std::vector<std::string> m_in_content{};
    std::vector<std::string> m_out_content{};
public:
    qtranslator(int ac, char **av);
    ~qtranslator() = default;

    void parse_args(int ac, char **av);
    void parse_file();
    void write_to_qasm();

    static void help(const char *bin, int return_val);
};