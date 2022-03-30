/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sub
*/

#include "dylib.hpp"

#include "Instruction.hpp"

#include <math.h>
#include <vector>

static void createInputState(QRegister &reg, size_t n)
{
    reg.h(n);
    for (size_t i = 0; i < n; i++)
        reg.cp(pow(2, i + 1), n, reg, n - (i + 1));
}

static void evolveQFTState(QRegister &reg_a, QRegister &reg_b, size_t n)
{
    for (size_t i = 0; i <= n; i++)
        reg_a.cp(pow(2, i), n , reg_b, n - i);
}

static void inverseQFT(QRegister &reg, size_t n)
{
    for (size_t i = 0; i < n; i++)
        reg.cp(-1 * pow(2, n - i), n, reg, i);
    reg.h(n);
}

static void doSub(QRegister &q1, QRegister &q2)
{
    size_t size = q1.getSize() - 1;
    q1.setValue(q2.getValue() - q1.getValue());

    q1.x();
    for (size_t i = 0; i <= size; i++)
        createInputState(q1, size - i);
    for (size_t i = 0; i <= size; i++)
        evolveQFTState(q1, q2, size - i);
    for (size_t i = 0; i <= size; i++)
        inverseQFT(q1, i);
    q1.x();
}

static void uniSub(QRegister &qreg1, QRegister &qreg2, std::string arg)
{
    int value = std::stoul(arg.substr(1), nullptr, 16);
    qreg1.reset();
    qreg1.fillQRegister(value);
    doSub(qreg2, qreg1);
}

class Sub : public Instruction {
    public:
        Sub(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "sub"; }
        void run(Circuit &circ) override {
            if (_args[0][0] == '$') {
                uniSub(*circ.getReg("add"), *circ.getReg(_args[1]), _args[0]);
            } else
                doSub(*circ.getReg(_args[1]), *circ.getReg(_args[0]));
            }
    private:
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Sub(args);
}