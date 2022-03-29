/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Add
*/

#ifndef ADD_HPP_
#define ADD_HPP_

#include "Instruction.hpp"
#include <vector>

class Add : public Instruction {
    public:
        Add(const std::vector<std::string>args): _args(args) {};
        virtual void run(Circuit &circ);
    private:
        std::vector<std::string> _args;
};

#endif /* !ADD_HPP_ */