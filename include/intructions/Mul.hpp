/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Mul
*/

#ifndef MUL_HPP_
#define MUL_HPP_

#include "Instruction.hpp"
#include <vector>

class Mul : public Instruction {

    public:
        Mul(const std::vector<std::string>args) { _args = args;};
        virtual void run(Circuit &circ);
    private:
        std::vector<std::string> _args;
};

#endif /* !MUL_HPP_ */
