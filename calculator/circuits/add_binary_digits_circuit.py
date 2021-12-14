import qiskit


class addBitsCircuit:
    def __init__(self, firstBit: bool, secondBit: bool):
        self.circuit = qiskit.QuantumCircuit(4, 2)
        if (firstBit):
            self.circuit.x(0)
        if (secondBit):
            self.circuit.x(1)
        self.circuit.barrier()
        self.circuit.cx(0, 2)
        self.circuit.cx(1, 2)
        self.circuit.ccx(0, 1, 3)
        self.circuit.barrier()
        self.circuit.measure(2, 0)
        self.circuit.measure(3, 1)
