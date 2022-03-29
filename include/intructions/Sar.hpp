/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sar
*/

#ifndef Sar_HPP_
#define Sar_HPP_

#include "Instruction.hpp"
#include <vector>

class Sar : public Instruction {
    public:
        Sar(const std::vector<std::string>args): _args(args) {};
        void run(Circuit &circ) override;
    private:
        std::vector<std::string> _args;
};

#endif /* !Sar_HPP_ */
