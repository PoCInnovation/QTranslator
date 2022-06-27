#pragma once

#include "tools.hpp"
#include "QRegister.hpp"
#include "Circuit.hpp"
#include "Instruction.hpp"
#include "dylib.hpp"

#include <functional>
#include <sstream>
#include <vector>
#include <string>
#include <map>

/**
 *  This namespace contains parsing functions used during transpilation
 */
namespace parser {
    static std::vector<dylib> dynamic_libs;
    static std::map<std::string, std::function<Instruction*(std::vector<std::string>)>> IntructionsTab;

    std::vector<Instruction*> parceAsm(std::vector<std::string> cmdAsm);
    std::vector<std::string> parceBinary(std::string filepath);
}
