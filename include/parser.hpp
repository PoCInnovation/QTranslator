#pragma once


#include "Move.hpp"
#include "Add.hpp"
#include "Sub.hpp"
#include "tools.hpp"
#include "QRegister.hpp"
#include "Circuit.hpp"
#include "Mul.hpp"
#include "Div.hpp"
#include "Sar.hpp"
#include "Shr.hpp"
#include "Shl.hpp"

#include <sstream>
#include <vector>
#include <string>
#include <map>

/**
 *  This namespace contains parsing functions used during transpilation
 */
namespace parser {
    typedef Instruction* (*Creator)(std::vector<std::string>);
    template <typename T>
    static Instruction* make(std::vector<std::string> args) { return new T(args); }

    static const std::map<std::string, Creator> IntructionsTab = {
        {"add", make<Add>},
        {"mov", make<Move>},
        {"sub", make<Sub>},
        {"imul", make<Mul>},
        {"idivl", make<Div>},
        {"sar", make<Sar>},
        {"shr", make<Shr>},
        {"shl", make<Shl>}
    };
    std::vector<Instruction*> parceAsm(std::vector<std::string> cmdAsm);
    std::vector<std::string> parceBinary(std::string filepath);
}
