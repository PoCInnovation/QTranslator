from typing import Dict
from qiskit import IBMQ, Aer
import qiskit

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
