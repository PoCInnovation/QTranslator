
#include <vector>
#include <string>
#include <iostream>

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <map>
#include "Move.hpp"
#include "Add.hpp"
#include "tools.hpp"
#include <sstream>
#include <QRegister.hpp>
#include <Circuit.hpp>

typedef Instruction* (*Creator)(std::vector<std::string>);

template <typename T>
static Instruction* make(std::vector<std::string> args) { return new T(args); }

std::map<std::string, Creator> IntructionsTab = {{"add", make<Add>}, {"mov", make<Move>}};

template<typename Map> typename Map::const_iterator
find_prefix(Map const& map, typename Map::key_type const& key)
{
    typename Map::const_iterator it = map.upper_bound(key);
    while (it != map.begin()) {
        --it;
        if(key.substr(0, it->first.size()) == it->first)
            return it;
    }
    return map.end(); // map contains no prefix
}

std::vector<std::string> parceBinary(std::string filepath)
{
    std::string cmd = ("objdump -d " + filepath  + "| awk -v RS= '/^[[:xdigit:]]+ <main>/'");
    char buf[BUFSIZ];
    FILE *ptr = popen(cmd.c_str(), "r");
    std::vector<std::string> cmdAsm;
    std::string temp;
    int i = 0;

    fgets(buf, BUFSIZ, ptr);
    while (fgets(buf, BUFSIZ, ptr) != NULL) {
        temp = buf;
        if (temp[temp.size() - 1] == '\n')
            temp.pop_back();
        cmdAsm.push_back(temp);
        i++;
    }
    pclose(ptr);
    return cmdAsm;
}

std::vector<Instruction*> parceAsm(std::vector<std::string> cmdAsm)
{
    std::vector<Instruction*> instructionsList;
    std::string temp;
    std::vector<std::string> tempCmd;

    for (auto line : cmdAsm) {
        if (line.size() > 32) {
            temp = line.substr(32).c_str();
            tempCmd = tools::string_to_vector(temp, ' ', false);
            auto t = find_prefix(IntructionsTab, tempCmd[0]);
            if (t != IntructionsTab.end())
                instructionsList.push_back((*t).second(tools::string_to_vector(tempCmd[1], ',', false)));
        }
    }
    return instructionsList;
}

int main(void)
{
    Circuit circ; circ.redirecCout();
    std::vector<std::string> cmdAsm = parceBinary("c.asm");
    std::vector<Instruction*> instructionsList = parceAsm(cmdAsm);

    circ.addReg("add", 0);
    std::cout << "qreg cin[1];" << std::endl;
    std::cout << "qreg cout[1];" << std::endl;

    for(auto t : instructionsList)
        t->run(circ);

    circ.getReg("%eax")->measure();

    circ.draw();
    return 0;
}