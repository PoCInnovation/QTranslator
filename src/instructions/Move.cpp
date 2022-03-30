/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Move
*/

#include "dylib.hpp"

#include "Instruction.hpp"
#include <vector>
#include <iostream>

class Move : public Instruction {
    public:
        Move(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "move"; }
        void run(Circuit &circ) override {
            if (_args[0][0] == '$')
                movValue(circ);
            else
                movReg(circ);
        }
    private:
        void movValue(Circuit &circ) {
            int value = std::stoul(_args[0].substr(1), nullptr, 16);
            QRegister *q2 = circ.getReg(_args[1]);

            if (q2 == nullptr)
                circ.addReg(_args[1], value);
            else {
                q2->reset();
                q2->fillQRegister(value);
            }
        }
        void movReg(Circuit &circ) {
            QRegister *q1 = circ.getReg(_args[0]);
            QRegister *q2 = circ.getReg(_args[1]);
            QRegister *temp;

            if (q1 == nullptr)
                q1 = circ.addReg(_args[0], 0);
            if (q2 == nullptr)
                circ.addReg(_args[1], *q1);
            else {
                temp = circ.getReg("add");
                temp->reset();
                q2->reset();
                temp->cx(*q1);
                q2->cx(*temp);
            }
        }
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Move(args);
}