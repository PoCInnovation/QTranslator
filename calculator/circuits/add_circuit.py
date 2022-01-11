from qiskit import ClassicalRegister, QuantumRegister, Aer, QuantumCircuit, execute
import operator
from math import pi
class ArithmeticCircuit:
    def fillRegister(self, register, number, length):
        i = 0
        for bit in number:
            if bit == "1":
                self.circ.x(register[length - (i + 1)])
            i += 1

    def createInputState(self, reg, n):
        self.circ.h(reg[n])
        for i in range(n):
            self.circ.cp(pi / float(2 ** (i + 1)), reg[n - (i + 1)], reg[n])

    def evolveQFTState(self, reg_a, reg_b, n):
        for i in range(n + 1):
            self.circ.cp(pi / float(2 ** (i)), reg_b[n - i], reg_a[n])

    def inverseQFT(self, reg, n):
        for i in range(0, n):
            self.circ.cp(-1 * pi / float(2 ** (n - i)), reg[i], reg[n])
        self.circ.h(reg[n])

    def __init__(self, n1, n2, op="ADD") -> str:
        ## get args
        l1 = len(n1)
        l2 = len(n2)
        if l2 > l1:
            n1, n2 = n2, n1
            l2, l1 = l1, l2
        n2 = ("0") * (l1 - l2) + n2
        size = l1

        ## Init
        self.qreg1 = QuantumRegister(size + 1)
        self.qreg2 = QuantumRegister(size + 1)
        self.outreg = ClassicalRegister(size + 1)
        self.circ = QuantumCircuit(self.qreg1, self.qreg2, self.outreg)
        self.fillRegister(self.qreg1, n1, size)
        self.fillRegister(self.qreg2, n2, size)

        ## Calc
        if op == "SUB":
            self.circ.x(self.qreg1)
        for i in range(size + 1):
            self.createInputState(self.qreg1, size - i)
        for i in range(size + 1):
            self.evolveQFTState(self.qreg1, self.qreg2, size - i)
        for i in range(size + 1):
            self.inverseQFT(self.qreg1, i)
        if op == "SUB":
            self.circ.x(self.qreg1)

        ## Get result
        for i in range(size + 1):
            self.circ.measure(self.qreg1[i], self.outreg[i])

