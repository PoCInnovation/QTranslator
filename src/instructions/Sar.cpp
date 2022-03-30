/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sar
*/

#include "dylib.hpp"

#include "Instruction.hpp"
#include <vector>

static void shiftRight(Circuit &circ, size_t nbtime, const std::string &reg_name)
{
    QRegister *reg = circ.getReg(reg_name);
    QRegister *reg_add = circ.getReg("add");

    reg_add->reset();
    reg_add->cx(*reg);
    reg->reset();
    for (size_t i = nbtime; i < reg->getSize() - nbtime; i++)
        reg->cx(i - nbtime, i, *reg_add);
}

class Sar : public Instruction {
    public:
        Sar(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "sar"; }
        void run(Circuit &circ) override {
            if (_args[0][0] == '$') {
                shiftRight(circ, std::stoul(_args[0].substr(1), nullptr, 16), _args[1]);
            } else
                shiftRight(circ, 1, _args[0]);
            }
    private:
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Sar(args);
}