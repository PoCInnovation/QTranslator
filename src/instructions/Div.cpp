/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Div
*/

#include "dylib.hpp"

#include "Instruction.hpp"
#include <vector>

class Div : public Instruction {
    public:
        Div(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "idiv"; }
        void run(Circuit &circ) override {
            QRegister &reg_1 = *circ.getReg("%eax");
            QRegister &reg_2 = *circ.getReg(_args[0]);

            reg_1.reset();
            reg_1.fillQRegister(reg_1.getValue() / reg_2.getValue());
        }
    private:
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Div(args);
}