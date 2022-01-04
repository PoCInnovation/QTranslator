# Load IBMQ backend
######
from qiskit import IBMQ

IBMQ.save_account("IBM_TOKEN")
provider = IBMQ.load_account()
backend = provider.get_backend("ibmq_qasm_simulator")
######

import qiskit
import sys

if len(sys.argv) != 2:
    sys.exit(-1)
else:
    file_name = sys.argv[1]

provider = IBMQ.load_account()
backend = provider.get_backend("ibmq_qasm_simulator")

circ = qiskit.QuantumCircuit.from_qasm_file(file_name)
job = qiskit.execute(circ, backend)

job_stats = job.result().get_counts()
print(job_stats)
