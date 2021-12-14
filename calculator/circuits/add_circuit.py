from qiskit import ClassicalRegister, QuantumRegister
from qiskit import QuantumCircuit


class AddCircuit:
    def fillRegister(self, register, number, length):
        i = 0
        for bit in number:
            if bit == "1":
                self.circuit.x(register[length - (i + 1)])
            i += 1

    def __init__(self, first, second):
        length = len(first)
        length2 = len(second)

        if length > 8 or length2 > 8:
            print("Please enter valid binary numbers inputs (less than 8 bits).")
            exit()

        maxLength = max(length, length2)

        firstNumber = QuantumRegister(maxLength)
        secondNumber = QuantumRegister(maxLength + 1)
        carry = QuantumRegister(maxLength)
        output = ClassicalRegister(maxLength + 1)

        self.circuit = QuantumCircuit(firstNumber, secondNumber, carry, output)

        self.fillRegister(firstNumber, first, length)
        self.fillRegister(secondNumber, second, length2)

        for i in range(maxLength - 1):
            self.circuit.ccx(firstNumber[i], secondNumber[i], carry[i + 1])
            self.circuit.cx(firstNumber[i], secondNumber[i])
            self.circuit.ccx(carry[i], secondNumber[i], carry[i + 1])

        self.circuit.ccx(firstNumber[maxLength - 1], secondNumber[maxLength - 1], secondNumber[maxLength])
        self.circuit.cx(firstNumber[maxLength - 1], secondNumber[maxLength - 1])
        self.circuit.ccx(carry[maxLength - 1], secondNumber[maxLength - 1], secondNumber[maxLength])

        self.circuit.cx(carry[maxLength - 1], secondNumber[maxLength - 1])

        for i in range(maxLength - 1):
            self.circuit.ccx(carry[(maxLength - 2) - i], secondNumber[(maxLength - 2) - i], carry[(maxLength - 1) - i])
            self.circuit.cx(firstNumber[(maxLength - 2) - i], secondNumber[(maxLength - 2) - i])
            self.circuit.ccx(firstNumber[(maxLength - 2) - i], secondNumber[(maxLength - 2) - i], carry[(maxLength - 1) - i])

            self.circuit.cx(carry[(maxLength - 2) - i], secondNumber[(maxLength - 2) - i])
            self.circuit.cx(firstNumber[(maxLength - 2) - i], secondNumber[(maxLength - 2) - i])

        for i in range(maxLength + 1):
            self.circuit.measure(secondNumber[i], output[i])

