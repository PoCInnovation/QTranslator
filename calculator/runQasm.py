import qiskit

simulator = qiskit.Aer.get_backend('qasm_simulator')
circuit = qiskit.QuantumCircuit().from_qasm_file("c.qasm")
output = qiskit.execute(circuit, simulator).result().get_counts()

print(output)