/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** QRegister
*/

#include "QRegister.hpp"
#include "bitset"

void QRegister::fillQRegister(int value)
{
    size_t index = 0;
    std::string bitString = std::bitset<8>(value).to_string();

    this->_size = bitString.length();
    for (const char c : bitString) {
        if (c == '1')
            this->x(this->_size - index - 1);
        index++;
    }
    this->_size = 9;
    this->_value = value;
}

void QRegister::reset()
{
    std::cout << __func__ << " " << _name << ";" << std::endl;
}

QRegister::QRegister(int value, const size_t id): _name("q" + std::to_string(id)), _size(0), _value(0)
{
    this->fillQRegister(value);
}

QRegister::QRegister(const QRegister &other, const size_t id): _name("q" + std::to_string(id)), _size(other._size), _value(other.getValue())
{
    cx(other);
}

const std::string &QRegister::getName(void) const
{
    return this->_name;
}

size_t QRegister::getSize(void) const
{
    return this->_size;
}

const std::string QRegister::qRegAt(size_t index) const
{
    return this->_name + "[" + std::to_string(index) + "]";
}

QRegister::~QRegister()
{}

void QRegister::setValue(size_t v)
{
    _value = v;
}

size_t QRegister::getValue(void) const
{
    return _value;
}

// QASM Instructions
void QRegister::x()
{
    std::cout << __func__ << " ";
    std::cout << this->getName() << ";" << std::endl;
}

void QRegister::x(size_t index)
{
    std::cout << __func__ << " ";
    std::cout << qRegAt(index) + ";" << std::endl;
}

void QRegister::cx(const QRegister &other)
{
    std::cout << __func__ << " ";
    std::cout << other.getName() << "," << this->getName() << ";" << std::endl;
}

void QRegister::cx(size_t index, const QRegister &other)
{
    std::cout << __func__ << " ";
    std::cout << other.qRegAt(index) << "," << this->qRegAt(index) << ";" << std::endl;
}

void QRegister::cx(size_t curindex, size_t index, const QRegister &other)
{
    std::cout << __func__ << " ";
    std::cout << other.qRegAt(index) << "," << this->qRegAt(curindex) << ";" << std::endl;
}

void QRegister::h()
{
    std::cout << __func__ << " ";
    std::cout << this->getName() << ";" << std::endl;
}

void QRegister::h(size_t index)
{
    std::cout << __func__ << " ";
    std::cout << this->qRegAt(index) << ";" << std::endl;
}

void QRegister::cp(int divPi, size_t index, QRegister &other, size_t otherIndex)
{
    std::cout << __func__ << "(pi/" + std::to_string(divPi) + ")";
    std::cout << other.qRegAt(otherIndex) << "," << this->qRegAt(index) << ";" << std::endl;
}

void QRegister::measure()
{
    std::cout << "measure " << this->getName() << " -> " << "c0;" << std::endl;
}

void QRegister::measure(size_t index)
{
    std::cout << "measure " << qRegAt(index) << " -> " << "c0[" << std::to_string(index) << "];" << std::endl;
}