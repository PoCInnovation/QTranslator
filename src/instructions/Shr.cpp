/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sar
*/

#include "dylib.hpp"

#include "Instruction.hpp"
#include <vector>

class Shr : public Instruction {
    public:
        Shr(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "shr"; }
        void run(Circuit &circ) override {
            QRegister *reg = circ.getReg(_args[1]);
            reg->reset();
        }
    private:
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Shr(args);
}