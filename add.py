import qiskit
from add_circuit import addCircuit
import sys

if len(sys.argv) != 3:
    print("Please provide two binary numbers as argument")
    exit()

addCircuit = addCircuit(sys.argv[1], sys.argv[2])

simulator = qiskit.Aer.get_backend('qasm_simulator')

number_measurement = 2

output = qiskit.execute(addCircuit.circuit, simulator, shots=number_measurement).result().get_counts()

print(f'{sys.argv[1]} + {sys.argv[2]} =', list(output)[0])
