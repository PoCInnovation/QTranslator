import sys
from simulator import simulator
from ibm_exec import ibm_exec
from circuits.add_circuit import ArithmeticCircuit

if len(sys.argv) < 4 or len(sys.argv) > 5:
    print("Please provide an operation and two numbers as argument")
    exit()

if len(sys.argv) == 5:
    backend = sys.argv[4]
else:
    backend = 'qiskit'

first = '{0:{fill}3b}'.format(int(sys.argv[2]), fill='0')
second = '{0:{fill}3b}'.format(int(sys.argv[3]), fill='0')

if (sys.argv[1] == "ADD"):
    circuit = ArithmeticCircuit(first, second)
elif (sys.argv[1] == "MUL"):
    circuit = ArithmeticCircuit(first, second, "MUL")
elif (sys.argv[1] == "SUB"):
    circuit = ArithmeticCircuit(first, second, "SUB")
else:
    print("Please provide an operation and two numbers as argument")


if (backend == 'ibm'):
    output = ibm_exec(circuit.circ, send_to_ibm=True)
else:
    output = simulator(circuit.circ)

#print(f'Computed from {backend}:')
#print(f'{sys.argv[1]} {sys.argv[2]} {sys.argv[3]} =', output)
print(output)
