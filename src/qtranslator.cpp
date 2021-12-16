#include <iostream>
#include <string_view>
#include "qtranslator.hpp"
#include "exception.hpp"
#include "tools.hpp"
#include "format.hpp"
#include "parser.hpp"

qtranslator::qtranslator(int ac, char **av)
{
    parse_args(ac, av);
    parse_file();
    write_to_qasm();
}

void qtranslator::help(const char *bin, int return_val)
{
    std::cout << "USAGE:\n";
    std::cout << "\t" << bin << " file.io [OPTIONS]\n\n";

    std::cout << "DESCRIPTION:\n";
    std::cout << "\tfile.io\t\tfile to be translated into QASM\n\n";

    std::cout << "OPTIONS:\n";
    std::cout << "\t-h --help\tDisplay this help menu\n";
    std::cout << "\t-o --output\tName of the generated QASM file\n";

    std::cout << "RETURN VALUE:\n";
    std::cout << "\t0\t\tif transpilation succeed\n";
    std::cout << "\t1\t\tif transpilation failed\n";

    std::cout << std::flush;
    exit(return_val);
}

void qtranslator::parse_args(int ac, char **av)
{
    if (ac < 2)
        help(av[0], EXIT_FAILURE);
    if (std::string_view(av[1]) == "-h" or std::string_view(av[1]) == "--help")
        help(av[0], EXIT_SUCCESS);
    m_in = av[1];
    for (int i = 2; i < ac; i++) {
        std::string_view arg(av[i]);
        if (arg == "-h" or arg == "--help")
            help(av[0], EXIT_SUCCESS);
        else if (arg == "-o" or arg == "--output") {
            if (ac == i + 1)
                throw compiler::exception(format::bold, format::red, "error: ", format::reset, arg, " parameter needs to be specified");
            m_out = av[i + 1];
            i += 1;
        }
    }
}

void qtranslator::parse_file()
{
    m_in_content = tools::string_to_vector(tools::get_file_content(m_in), '\n');
    for (size_t i = 0; i < m_in_content.size(); i++) {
        auto parse = tools::string_to_vector(m_in_content[i], ' ');
        if (parse.empty())
            continue;
        try {
            m_out_content.push_back(parser::actions.at(parse.front())(parse));
        } catch (const compiler::exception &e) {
            throw compiler::exception(format::bold, m_in, ":", std::to_string(i + 1), ": ",
            format::red, "error: ", format::reset, format::bold, e.what(), "\n\t",
            format::reset, m_in_content[i], "\n\t", format::green, '^', format::reset);
        }
    }
}

void qtranslator::write_to_qasm()
{
    std::ofstream output;
    output.open(m_out);
    output << "OPENQASM 3;\n";
    output << "include \"stdgates.inc\";\n\n";
    for (auto &line : m_out_content)
        output << line << '\n';
    output.close();
}