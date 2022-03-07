/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Div
*/

#include "Div.hpp"
#include "Sub.hpp"
#include "Move.hpp"

void Div::run(Circuit &circ)
{
    QRegister &reg_1 = *circ.getReg("%eax");
    QRegister &reg_2 = *circ.getReg(_args[0]);

    reg_1.reset();
    reg_1.fillQRegister(reg_1.getValue() / reg_2.getValue());
}
