/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Move
*/

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "Instruction.hpp"
#include <vector>

class Move : public Instruction {
    public:
        Move(const std::vector<std::string>args) { _args = args;};
        virtual void run(Circuit &circ);
    private:
        void movValue(Circuit &circ);
        void movReg(Circuit &circ);
        std::vector<std::string> _args;
};

#endif /* !MOVE_HPP_ */
