/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sar
*/

#include "Sar.hpp"

void shiftRight(Circuit &circ, size_t nbtime, const std::string &reg_name)
{
    QRegister *reg = circ.getReg(reg_name);
    QRegister *reg_add = circ.getReg("add");

    reg_add->reset();
    reg_add->cx(*reg);
    reg->reset();
    for (size_t i = nbtime; i < reg->getSize() - nbtime; i++)
        reg->cx(i - nbtime, i, *reg_add);
}

void Sar::run(Circuit &circ)
{
    if (_args[0][0] == '$') {
        shiftRight(circ, std::stoul(_args[0].substr(1), nullptr, 16), _args[1]);
    } else
        shiftRight(circ, 1, _args[0]);
}