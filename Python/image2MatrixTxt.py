from PIL import Image
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

file_in = sys.argv[1]
file_out = file_in[:file_in.rfind('.')]+".mat"

if len(sys.argv) > 3:
    file_out = sys.argv[2]

img = Image.open(file_in).convert('L')
print(img.size)
# img.show()
pix = np.array(img.getdata()).reshape(img.size[1], img.size[0])
np.savetxt(file_out, pix, fmt='%d')
