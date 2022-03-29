/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Add
*/

#include "Add.hpp"
#include <iostream>
#include <math.h>

static void opAdd(QRegister &qreg1, QRegister &qreg2)
{
    qreg1.setValue(qreg2.getValue() + qreg1.getValue());
    std::cout << "reset cin;" << std::endl;
    std::cout << "reset cout;" << std::endl;
    std::cout << "majority cin[0]," + qreg1.getName() + "[0]," + qreg2.getName() + "[0];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[0]," + qreg1.getName() + "[1],"+ qreg2.getName() + "[1];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[1]," + qreg1.getName() + "[2],"+ qreg2.getName() + "[2];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[2]," + qreg1.getName() + "[3],"+ qreg2.getName() + "[3];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[3]," + qreg1.getName() + "[4],"+ qreg2.getName() + "[4];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[4]," + qreg1.getName() + "[5],"+ qreg2.getName() + "[5];" << std::endl;
    std::cout << "majority "+ qreg2.getName() + "[5]," + qreg1.getName() + "[6],"+ qreg2.getName() + "[6];" << std::endl;
    std::cout << "cx "+qreg2.getName() + "[6],cout[0];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[5]," + qreg1.getName() + "[6],"+ qreg2.getName() + "[6];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[4]," + qreg1.getName() + "[5],"+ qreg2.getName() + "[5];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[3]," + qreg1.getName() + "[4],"+ qreg2.getName() + "[4];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[2]," + qreg1.getName() + "[3],"+ qreg2.getName() + "[3];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[1]," + qreg1.getName() + "[2],"+ qreg2.getName() + "[2];" << std::endl;
    std::cout << "unmaj "+ qreg2.getName() + "[0]," + qreg1.getName() + "[1],"+ qreg2.getName() + "[1];" << std::endl;
    std::cout << "unmaj cin[0]," + qreg1.getName() + "[0],"+qreg2.getName() + "[0];" << std::endl;
    std::cout << "cx cout[0]," + qreg1.getName() + "[7];" << std::endl;
}

static void uniAdd(QRegister &qreg1, QRegister &qreg2, std::string arg)
{
    int value = std::stoul(arg.substr(1), nullptr, 16);

    qreg1.reset();
    qreg1.fillQRegister(value);
    opAdd(qreg2, qreg1);
}

void Add::run(Circuit &circ)
{
    if (_args[0][0] == '$') {
        uniAdd(*circ.getReg("add"), *circ.getReg(_args[1]), _args[0]);
    } else
        opAdd(*circ.getReg(_args[1]), *circ.getReg(_args[0]));
}
