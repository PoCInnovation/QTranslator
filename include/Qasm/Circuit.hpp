/*
** EPITECH PROJECT, 2022
** QTranslator
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "QRegister.hpp"
#include <map>
#include <string>
#include <sstream>
#include <memory>


/**
 * @brief All the instructions will be parse and interpret in this Class.
*/
class Circuit {
    public:
        /**
         * @brief Construct a new Quantum Circuit and setUp OpenQasm2 header
        */
        Circuit();
        /**
         * @brief clean the Quantum Circuit and output result
        */
        ~Circuit();

        // Cout
        /**
         * @brief Use to redirec cout to a buffer.
        */
        void redirecCout(void);
        /**
         * @brief Dump the Quantum Circuit on the standart output
        */
        void draw(void);
        /**
         * @brief Dump the Quantum Circuit in a file
        */
        void draw(const std::string &filePath);

        /**
         * @brief Get the redirected buffer of cout
        */
        const std::ostringstream &getBuffer(void) const;
        /**
         * @brief set the cout buffer to a new string
         * @param Buffer String that will set as new buffer
        */
        void setBuffer(const std::string &buffer);

        // Utils
        /**
         * @brief Get Quantum Register from Circuit
         * @param regKey-StringKey of a reg
        */
        QRegister *getReg(const std::string &regKey);
        /**
         * @brief Create a new Quantum Register in the ciruit
         * @param regKey-StringKey of the new Quantum Register
         * @param value Quantum Register will be init to that value
        */
        QRegister *addReg(const std::string &regKey, int value);
        /**
         * @brief Create a new Quantum Register in the ciruit from a other Register
         * @param regKey-StringKey of the new Quantum Register
         * @param Other Quantum Register to init the new Register
        */
        QRegister *addReg(const std::string &regKey, QRegister &other);
    private:
        std::string _header;
        std::ostringstream _coutBuffer;
        std::unique_ptr<std::streambuf> _oldBuffer;
        std::map<std::string, QRegister*> _regs;
        size_t _nb;
};

#endif /* !CIRCUIT_HPP_ */
