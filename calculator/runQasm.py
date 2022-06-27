from typing import Dict
from qiskit import IBMQ, Aer
import qiskit
import sys

def ibm_exec(circuit, number_measurement=1):
    IBMQ.save_account("IBM TOKEN", overwrite=True)

def ibm_exec(circuit, number_measurement=1, send_to_ibm=False) -> Dict[str, int]:

    if send_to_ibm:
        provider = IBMQ.load_account()
        backend = provider.get_backend("ibmq_qasm_simulator")
    else:
        backend = Aer.get_backend("qasm_simulator")

    output = (
        qiskit.execute(circuit, backend, shots=number_measurement).result().get_counts()
    )
    return output


ibm : bool = False

if len(sys.argv) > 2 and sys.argv[2] == "ibm":
    ibm = True

simulator = qiskit.Aer.get_backend('qasm_simulator')
circuit = qiskit.QuantumCircuit().from_qasm_file(sys.argv[1])
output = ibm_exec(circuit, 1, ibm)

best_key : str = ""
best_stat : int = 0

for (key, stat) in output.items():
    if best_stat <= stat:
        best_stat = stat
        best_key = key

print("Result is", int(best_key, 2))