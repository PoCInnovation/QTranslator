import qiskit
from add_binary_digits_circuit import addBitsCircuit
import sys

if len(sys.argv) != 3:
    print("Please provide two binary number as argument")
    exit()

addCircuit = addBitsCircuit(int(sys.argv[1]), int(sys.argv[2]))

simulator = qiskit.Aer.get_backend('qasm_simulator')

output = qiskit.execute(addCircuit.circuit, simulator).result().get_counts()

print(f'{sys.argv[1]} + {sys.argv[2]} =', list(output)[0])
