import sys
from simulator import simulator
from ibm_exec import send_qasm
from circuits.add_circuit import AddCircuit

def invert_int(n):
    number_bit_len = n.bit_length()
    max_val = (2 ** number_bit_len) - 1
    return ~n & max_val

if len(sys.argv) < 4 or len(sys.argv) > 5:
    print("Please provide an operation and two numbers as argument")
    exit()

if len(sys.argv) == 5:
    backend = sys.argv[4]
else:
    backend = 'qiskit'

first = bin(int(sys.argv[2]))[2:]
second = bin(int(sys.argv[3]))[2:]

if (sys.argv[1] == "ADD"):
    circuit = AddCircuit(first, second)
elif (sys.argv[1] == "SUB"):
    circuit = AddCircuit(first, invert_number(second) + 1)
else:
    print("Please provide an operation and two numbers as argument")


if (backend == 'ibm'):
    output = ibm_exec(circuit.circuit)
    pass
else:
    output = simulator(circuit.circuit)

print(f'Computed from {backend}:')
print(f'{sys.argv[1]} {sys.argv[2]} {sys.argv[3]} =', output)
exit(output);
