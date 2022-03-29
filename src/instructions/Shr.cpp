/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Sar
*/

#include "Shr.hpp"

void Shr::run(Circuit &circ)
{
    QRegister *reg = circ.getReg(_args[1]);
    reg->reset();
}