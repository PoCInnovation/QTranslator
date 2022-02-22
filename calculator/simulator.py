import qiskit

def simulator(circuit, number_measurement=5):
    simulator = qiskit.Aer.get_backend('qasm_simulator')
    output = qiskit.execute(circuit, simulator, shots=number_measurement).result().get_counts()
    return int(list(output)[0], 2)
