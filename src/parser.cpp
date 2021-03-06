
#include <filesystem>
#include "parser.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define POPEN(cmd, mode) _popen(cmd, mode)
#define PCLOSE(pipe) _pclose(pipe)
#else
#define POPEN(cmd, mode) popen(cmd, mode)
#define PCLOSE(pipe) pclose(pipe)
#endif

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

std::vector<std::string> parser::parceBinary(std::string filepath)
{
    std::string cmd = ("objdump -d " + filepath  + " | awk -v RS= '/^[[:xdigit:]]+ <main>/'");
    char buf[BUFSIZ];
    FILE *ptr = POPEN(cmd.c_str(), "r");
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
    PCLOSE(ptr);
    return cmdAsm;
}

void load_instructions()
{
    for (auto &file : std::filesystem::recursive_directory_iterator("./instructions")) {
        if (file.path().extension() == dylib::extension) {
            try {
                dylib lib(file.path().string());
                auto fn = lib.get_function<Instruction *(std::vector<std::string>)>("get_instruction");
                std::unique_ptr<Instruction> mod(fn(std::vector<std::string>()));
                parser::IntructionsTab[mod->getName()] = fn;
                parser::dynamic_libs.push_back(std::move(lib));
            } catch (const dylib::handle_error &) {
                std::cerr << "Failed to load lib: " << file.path().string() << std::endl;
            } catch (const dylib::symbol_error &) {
                std::cerr << "Failed to load symbol \"get_instruction\" on lib: " << file.path().string() << std::endl;
            }
        }
    }
}

std::vector<Instruction*> parser::parceAsm(std::vector<std::string> cmdAsm)
{
    std::vector<Instruction*> instructionsList;
    std::string temp;
    std::vector<std::string> tempCmd;

    load_instructions();

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
