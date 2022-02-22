/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Circuit
*/

#include "Circuit.hpp"

Circuit::Circuit(): _oldBuffer(nullptr)
{
    _header.append("OPENQASM 2.0;\n");
    _header.append("include \"qelib1.inc\";\n");
    _header.append("include \"add.inc\";\n");
}

Circuit::~Circuit()
{
    if (_oldBuffer != nullptr)
        std::cout.rdbuf(_oldBuffer);
}

void Circuit::redirecCout(void) {
    this->_oldBuffer = std::cout.rdbuf();
    std::cout.rdbuf(_coutBuffer.rdbuf());
}

void Circuit::draw(void)
{
    if (_oldBuffer == nullptr)
        return;
    // Set Cout to terminal
    std::cout.rdbuf(_oldBuffer);
    // include
    std::cout << _header;
    // QuantumReg
    for (const auto &t : _regs)
        std::cout << "qreg " << t.second->qRegAt(t.second->getSize()) + ";" << std::endl;
    // ClassicalReg of output
    std::cout << "creg " << "c0[9];" << std::endl;
    // Qasm
    std::cout << _coutBuffer.str();
    _oldBuffer = nullptr;
}

const std::ostringstream &Circuit::getBuffer(void) const
{
    return _coutBuffer;
}

void Circuit::setBuffer(const std::string &buffer)
{
    _coutBuffer.str(buffer);
}

QRegister *Circuit::getReg(const std::string &regKey)
{
    return _regs[regKey];
}

QRegister *Circuit::addReg(const std::string &regKey, int value)
{
    QRegister *temp = new QRegister(value);

    _regs[regKey] = temp;
    return temp;
}

QRegister *Circuit::addReg(const std::string &regKey, QRegister &other)
{
    QRegister *temp = new QRegister(other);

    _regs[regKey] = temp;
    return temp;
}

