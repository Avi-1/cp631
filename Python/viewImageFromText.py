import sys
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

file_in = sys.argv[1]
img = np.loadtxt(file_in)
plt.imshow(img, cmap="gray")
plt.savefig("bioinnova_filter.png")
