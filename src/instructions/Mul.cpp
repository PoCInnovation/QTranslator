/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Mul
*/

#include "dylib.hpp"

#include "Instruction.hpp"
#include <vector>
#include <math.h>

static void executeQFT(QRegister &reg, size_t n)
{
    reg.h(n);
    for (size_t i = 0; i < n; i++)
        reg.cp(pow(2, i + 1), n, reg, n - (i + 1));
}

static void evolveQFTStateSum(QRegister &reg_a, QRegister &reg_b, size_t n)
{
    size_t l = reg_a.getSize();

    for (size_t i = 0; i <= n; i++) {
        if (n - i > l - 1)
            continue;
        reg_a.cp(pow(2, i), n, reg_b, n - i);
    }
}

static void inverseQFT(QRegister &reg, size_t n)
{
    for (size_t i = 0; i < n; i++)
        reg.cp(-1 * pow(2, n - i), n, reg, i);
    reg.h(n);
}

class Mul : public Instruction {

    public:
        Mul(const std::vector<std::string>args): _args(args) {};
        const char *getName() const override { return "mul"; }
        void run(Circuit &circ) override {
            QRegister &reg_1 = *circ.getReg(_args[0]);
            QRegister &reg_2 = *circ.getReg(_args[1]);
            size_t size = reg_2.getSize() - 1;
            size_t nb = reg_2.getValue();

            reg_2.reset();
            for (size_t i = 0; i <= size; i++)
                executeQFT(reg_2, size - i);
            for (size_t j = 0; j < nb; j++)
                for (size_t i = 0; i <= size; i++)
                    evolveQFTStateSum(reg_2, reg_1, size - i);
            for (size_t i = 0; i <= size; i++)
            inverseQFT(reg_2, i);
        }
    private:
        std::vector<std::string> _args;
};

DYLIB_API Instruction *get_instruction(std::vector<std::string> args)
{
    return new Mul(args);
}