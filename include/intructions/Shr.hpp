/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Shr
*/

#ifndef Shr_HPP_
#define Shr_HPP_

#include "Instruction.hpp"
#include <vector>

class Shr : public Instruction {
    public:
        Shr(const std::vector<std::string>args) { _args = args;};
        void run(Circuit &circ) override;
    private:
        std::vector<std::string> _args;
};

#endif /* !Shr_HPP_ */
