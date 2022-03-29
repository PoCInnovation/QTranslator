/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sub
*/

#ifndef SUB_HPP_
#define SUB_HPP_

#include "Instruction.hpp"
#include <vector>

class Sub : public Instruction {
    public:
        Sub(const std::vector<std::string>args): _args(args) {};
        virtual void run(Circuit &circ);
    private:
        std::vector<std::string> _args;
};

#endif /* !SUB_HPP_ */

