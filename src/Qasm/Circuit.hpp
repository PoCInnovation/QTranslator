/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include <map>
#include <string>
#include <sstream>
#include "QRegister.hpp"

class Circuit {
    public:
        Circuit();
        ~Circuit();

        // Cout
        void redirecCout(void);
        void draw(void);
        const std::ostringstream &getBuffer(void) const;
        void setBuffer(const std::string &buffer);

        // Utils
        QRegister *getReg(const std::string &regKey);
        QRegister *addReg(const std::string &regKey, int value);
        QRegister *addReg(const std::string &regKey, QRegister &other);
    private:
        std::ostringstream _coutBuffer;
        std::streambuf* _oldBuffer;
        std::map<std::string, QRegister*> _regs;
};

#endif /* !CIRCUIT_HPP_ */
