#include <iostream>
#include <fstream>
#include <string_view>
#include <filesystem>

#include "qtranslator.hpp"
#include "exception.hpp"
#include "tools.hpp"
#include "format.hpp"
#include "parser.hpp"

qtranslator::qtranslator(int ac, char const *av[]): _circ()
{
    parse_args(ac, av);
    parse_file();
    write_to_qasm();
}

void qtranslator::help(const char *bin, int return_val)
{
    std::cout << "USAGE:\n";
    std::cout << "\t" << bin << " file.asm [OPTIONS]\n\n";

    std::cout << "DESCRIPTION:\n";
    std::cout << "\tfile.asm\tASM source code to be translated into QASM\n\n";

    std::cout << "OPTIONS:\n";
    std::cout << "\t-h --help\tDisplay this help menu\n";
    std::cout << "\t-o --output\tName of the generated QASM file\n";

    std::cout << "RETURN VALUE:\n";
    std::cout << "\t0\t\tif transpilation succeed\n";
    std::cout << "\t1\t\tif transpilation failed\n";

    std::cout << std::flush;
    std::exit(return_val);
}

void qtranslator::parse_args(int ac, char const *av[])
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
                throw transpiler::exception(0, format::bold, format::red, "error: ", format::reset,
                format::bold, arg, " parameter needs to be specified", format::reset);
            m_out = av[i + 1];
            i += 1;
        }
    }
}

std::string get_cursor_delta(const std::vector<std::string> &parse, const size_t &pos)
{
    std::string ret;
    for (size_t i = 0; i < pos; i++)
        ret += std::string(parse[i].size() + 1, ' ');
    return ret;
}

void qtranslator::parse_file()
{
    if (!std::filesystem::exists(m_in)) {
        std::cerr << m_in + ": No such file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    _circ.redirecCout();
    _cmdAsm = parser::parceBinary(m_in);
    _instructionsList = parser::parceAsm(_cmdAsm);
}

void qtranslator::write_to_qasm()
{
    _circ.addReg("add", 0);
    _circ.addReg("div", 0);
    std::cout << "qreg cin[1];" << std::endl;
    std::cout << "qreg cout[1];" << std::endl;

    for(auto t : _instructionsList)
        t->run(_circ);

    _circ.getReg("%eax")->measure();
    _circ.draw();
}
