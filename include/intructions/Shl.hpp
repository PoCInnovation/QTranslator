/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Shl
*/

#ifndef Shl_HPP_
#define Shl_HPP_

#include "Instruction.hpp"
#include <vector>

class Shl : public Instruction {
    public:
        Shl(const std::vector<std::string>args): _args(args) {};
        void run(Circuit &circ) override;
    private:
        std::vector<std::string> _args;
};

#endif /* !Shl_HPP_ */
