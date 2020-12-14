import sys
import matplotlib.pyplot as plt
import numpy as np

fname = sys.argv[1]
file_out = fname[:fname.rfind('.')] + ".pdf"
print("Save timingn plot to ", file_out)

dtype1 = np.dtype([('implementation', 'S20'),
                   ('kernel_size', 'i1'), ('time', 'f8')])
arr = np.loadtxt(fname, dtype=dtype1, delimiter=',')

serial = arr['implementation'] == b'serial'
cuda = arr['implementation'] == b'cuda'
mpi = arr['implementation'] == b'mpi'

plt.plot(arr['kernel_size'][serial], arr['time'][serial], label="Serial")
plt.plot(arr['kernel_size'][cuda], arr['time'][cuda], label="Cuda")
plt.plot(arr['kernel_size'][mpi], arr['time'][mpi], label="MPI")

plt.xlabel('Kernel size, pixels')
plt.ylabel('Time, s')
plt.title('Edge detection filter timing results')
plt.legend()
plt.savefig(file_out)
