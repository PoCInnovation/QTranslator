import sys
from simulator import simulator
from ibm_exec import ibm_exec
from circuits.add_circuit import AddCircuit

if len(sys.argv) < 4 or len(sys.argv) > 5:
    print("Please provide an operation and two numbers as argument")
    exit()

if len(sys.argv) == 5:
    backend = sys.argv[4]
else:
    backend = 'qiskit'

first = bin(int(sys.argv[2]))[2:]
second = bin(int(sys.argv[3]))[2:] if sys.argv[1] == "ADD" else "0" + bin(~int(sys.argv[3]) + 1)[3:]

if (sys.argv[1] == "ADD"):
    circuit = AddCircuit(first, second)
elif (sys.argv[1] == "SUB"):
    circuit = AddCircuit(first, second)
else:
    print("Please provide an operation and two numbers as argument")


if (backend == 'ibm'):
    output = ibm_exec(circuit.circuit)
else:
    output = simulator(circuit.circuit)

#print(f'Computed from {backend}:')
#print(f'{sys.argv[1]} {sys.argv[2]} {sys.argv[3]} =', output)
print(output);
