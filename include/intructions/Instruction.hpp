/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Instruction
*/

#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include "Circuit.hpp"

/**
 * @brief This is the Class interface for all C-asm instructions
 */
class Instruction {
    public:
        /**
         * @brief default destructor
         */
        virtual ~Instruction() {};
        /**
         * @brief Get the name or symbole of the C-asm instruction to be parse.
         */
        virtual const char *getName() const = 0;
        /**
         * @brief Once Parsed the instructions will be executed by this entry
         *
         * @param Circuit the circuit on which the instruction will be executed
         */
        virtual void run(Circuit &circ) = 0;
};

#endif /* !INSTRUCTION_HPP_ */
