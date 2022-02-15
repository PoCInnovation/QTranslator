/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Instruction
*/

#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include "Circuit.hpp"

class Instruction {
    public:
        virtual ~Instruction() {};
        virtual void run(Circuit &circ) = 0;
};

#endif /* !INSTRUCTION_HPP_ */
