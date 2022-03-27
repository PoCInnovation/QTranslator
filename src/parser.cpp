
#include "parser.hpp"

template<typename Map> typename Map::const_iterator
static find_prefix(Map const& map, typename Map::key_type const& key)
{
    typename Map::const_iterator it = map.upper_bound(key);
    while (it != map.begin()) {
        --it;
        if(key.substr(0, it->first.size()) == it->first)
            return it;
    }
    return map.end(); // map contains no prefix
}
#include <unistd.h>
#include <stdio.h>
std::vector<std::string> parser::parceBinary(std::string filepath)
{
    std::string cmd = ("objdump -d " + filepath  + " | awk -v RS= '/^[[:xdigit:]]+ <main>/'");
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

std::vector<Instruction*> parser::parceAsm(std::vector<std::string> cmdAsm)
{
    std::vector<Instruction*> instructionsList;
    std::string temp;
    std::vector<std::string> tempCmd;

    for (auto line : cmdAsm) {
        if (line.size() > 32) {
            temp = line.substr(32).c_str();
            tempCmd = tools::string_to_vector(temp, ' ', false);
            auto t = find_prefix(parser::IntructionsTab, tempCmd[0]);
            if (t != parser::IntructionsTab.end())
                instructionsList.push_back((*t).second(tools::string_to_vector(tempCmd[1], ',', false)));
        }
    }
    return instructionsList;
}
