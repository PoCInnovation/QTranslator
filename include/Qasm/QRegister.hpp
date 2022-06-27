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
#include <stack>

class QRegister {
    public:
        QRegister(int value, const size_t id);
        QRegister(const QRegister &other, const size_t id);
        ~QRegister();

        // utils
        const std::string qRegAt(size_t index) const;
        void fillQRegister(int value);
        void reset();
        void setValue(size_t);

        //Getters
        const std::string &getName(void) const;
        size_t getSize(void) const;
        size_t getValue(void) const;

        // Quantum Gate
        void x();
        void x(size_t index);
        void cx(const QRegister &other);
        void revertLastCx(void);
        void cx(size_t index, const QRegister &other);
        void cx(size_t curindex, size_t index, const QRegister &other);
        void h();
        void h(size_t index);
        void cp(int divPi, size_t index, QRegister &other, size_t otherIndex);

        // Quantum States
        void measure();
        void measure(size_t index);
    private:
        std::string _name;
        size_t _size;
        size_t _value;
        std::stack<std::string> _cxHistory;
};

#endif /* !QREGISTER_HPP_ */
