from qiskit import IBMQ, Aer
import qiskit

IBMQ.save_account(
    "795759d0b1ba76df4aeab4f9a20c4a47d83bffdc85dc347a216c399e130c5c4c139f87ef0b6b8df0565cee40460e14eb4e5d3d226977d5ef361628d64e8dabae"
)

def ibm_exec(circuit, number_measurement=1, send_to_ibm=False):

    if send_to_ibm:
        provider = IBMQ.load_account()
        backend = provider.get_backend("qasm_simulator_py")
    else:
        backend = Aer.get_backend("qasm_simulator")

    output = (
        qiskit.execute(circuit, backend, shots=number_measurement).result().get_counts()
    )
    return int(list(output)[0], 2)
