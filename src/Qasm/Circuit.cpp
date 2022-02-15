/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Circuit
*/

#include "Circuit.hpp"

Circuit::Circuit(): _oldBuffer(nullptr)
{
}

Circuit::~Circuit() {
    if (_oldBuffer != nullptr)
        std::cout.rdbuf(_oldBuffer);
}

void Circuit::redirecCout(void) {
    this->_oldBuffer = std::cout.rdbuf();
    std::cout.rdbuf(_coutBuffer.rdbuf());
}

void Circuit::draw(void) {
    if (_oldBuffer != nullptr) {
        std::cout.rdbuf(_oldBuffer);
        // include
        std::cout << "OPENQASM 2.0;" << std::endl;
        std::cout << "include \"qelib1.inc\";"  << "include \"add.inc\";" << std::endl;
        // QuantumReg
        for (const auto &t : _regs)
            std::cout << "qreg " << t.second->qRegAt(t.second->getSize()) + ";" << std::endl;
        // ClassicalReg
        std::cout << "creg " << "c0[8];" << std::endl;
        // Qasm
        std::cout << _coutBuffer.str();
        _oldBuffer = nullptr;
    }
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

