from qiskit import IBMQ
import qiskit
import sys

def ibm_exec(circuit):
    IBMQ.save_account("IBM_TOKEN")

    provider = IBMQ.load_account()
    backend = provider.get_backend("ibmq_qasm_simulator")

    output = qiskit.execute(circuit, backend, shots=number_measurement).result().get_counts()
    return int(list(output)[0], 2)