/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Div
*/

#ifndef DIV_HPP_
#define DIV_HPP_

#include "Instruction.hpp"
#include <vector>

class Div : public Instruction {
    public:
        Div(const std::vector<std::string>args) { _args = args;};
        virtual void run(Circuit &circ);
    private:
        std::vector<std::string> _args;
};

#endif /* !DIV_HPP_ */
