import sys
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

file_in = sys.argv[1]
file_out = file_in[:file_in.rfind('.')] + ".png"
print("Save to ", file_out)
img = np.loadtxt(file_in)
plt.imshow(img, cmap="gray")
plt.savefig(file_out)
