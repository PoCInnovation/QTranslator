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
        /**
         * @brief Construct a new Quantum Register (aka QRegister).
         * @param value The new QRegister will be init from it.
         * @param id the new QRegister id (generate by QCircuit)
        */
        QRegister(int value, const size_t id);
        /**
         * @brief Construct a new Quantum Register (aka QRegister) from a other.
         * @param other The new QRegister will be init is value from it.
         * @param id the new QRegister id (generate by QCircuit)
        */
        QRegister(const QRegister &other, const size_t id);
        /**
         * @brief clean the QRegister
        */
        ~QRegister();

        // utils
        /**
         * @brief Get the OpenQasm2 formated name of the QRegister.
        */
        const std::string qRegAt(size_t index) const;
        /**
         * @brief Set the QRegister to a new Value
         * @param value The QRegister will be fill from it.
        */
        void fillQRegister(int value);
        /**
         * @brief OpenQasm2 instruction to reset all Qbit to Stat |0>
        */
        void reset();
        /**
         * @brief reset the QRegister to a value
        */
        void setValue(size_t);

        //Getters
        const std::string &getName(void) const;
        size_t getSize(void) const;
        size_t getValue(void) const;

        // Quantum Gate
        /**
         * @brief OpenQasm2 instruction to appli a 'X' gate on all Qbit
        *   (|1> => |0>)
        */
        void x();
        /**
         * @brief OpenQasm2 instruction to appli a 'X' gate on a target Qbit.
         *  (|1> => |0>)
         * @param index The target Qbit index.
        */
        void x(size_t index);
        /**
         * @brief OpenQasm2 instruction to appli a 'CX' gate on all Qbit with
         * other QRegister as control register.
         *  (|1> + |1> => |0>  /  |1> + |0> => |1>)
         * @param other-The control QRegister.
        */
        void cx(const QRegister &other);
        /**
         * @brief Revert the last 'CX' gate instruction.
        */
        void revertLastCx(void);
        /**
         * @brief OpenQasm2 instruction to appli a 'CX' gate on a target Qbit with
         * other QRegister Qbit sas control Qubit.
         *  (|1> + |1> => |0>  /  |1> + |0> => |1>)
         * @param index The target Qbit index for both.
         * @param other-The control QRegister.
        */
        void cx(size_t index, const QRegister &other);
        /**
         * @brief OpenQasm2 instruction to appli a 'CX' gate on a target Qbit with
         * other QRegister an other index Qbit as control Qubit
         *  (|1> + |1> => |0>  /  |1> + |0> => |1>)
         * @param index The target Qbit index for target.
         * @param curindex The target Qbit index for controler.
         * @param other-The control QRegister.
        */
        void cx(size_t curindex, size_t index, const QRegister &other);
        /**
         * @brief OpenQasm2 instruction to appli a 'Hadamard' gate.
        */
        void h();
        /**
         * @brief OpenQasm2 instruction to appli a 'Hadamard' gate a target Qbit.
        */
        void h(size_t index);
        /**
         * @brief OpenQasm2 instruction to appplie a 'Underlying Gate' on the QRegister index Qbit with
         * other QRegister an other index Qbit as control Qbit
         * @param divPi The 'CP' gate need a angle of the rotation to applie.
         * @param index The target Qbit index for target.
         * @param other The control QRegister.
         * @param otherIndex The target Qbit index for controler.
         */
        void cp(int divPi, size_t index, QRegister &other, size_t otherIndex);

        // Quantum States
        /**
         * @brief OpenQasm2 instruction to measure a QRegister to Classique register.
        */
        void measure();
        /**
         * @brief OpenQasm2 instruction to measure a QRegister Qbit to Classique register Qbit.
         * @param index Qbit index
        */
        void measure(size_t index);
    private:
        std::string _name;
        size_t _size;
        size_t _value;
        std::stack<std::string> _cxHistory;
};

#endif /* !QREGISTER_HPP_ */
