/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** QRegister
*/

#ifndef QREGISTER_HPP_
#define QREGISTER_HPP_

#include <string>
#include <iostream>

class QRegister {
    public:
        QRegister(int value = 0);
        QRegister(const QRegister &other);
        ~QRegister();

        // utils
        const std::string qRegAt(size_t index) const;
        void fillQRegister(int value);
        void reset();

        //Getters
        const std::string &getName(void) const;
        const size_t getSize(void) const;

        // Quantum Gate
        void x();
        void x(size_t index);
        void cx(const QRegister &other);
        void cx(size_t index, const QRegister &other);
        void h();
        void h(size_t index);
        void cp(int divPi, size_t index, QRegister &other, size_t otherIndex);

        // Quantum States
        void measure();
        void measure(size_t index);
    private:
        std::string _name;
        size_t _size;
};

#endif /* !QREGISTER_HPP_ */
