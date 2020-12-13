from PIL import Image
import sys

Image.MAX_IMAGE_PIXELS = None
file_in = sys.argv[1]
file_out = sys.argv[2]
image_width = int(sys.argv[3])

if len(sys.argv) > 4:
    bw = True
else:
    bw = False

im = Image.open(file_in, "r")

pix_val = list(im.getdata())

pixel_grid = []

i=0
while i < len(pix_val):
    pixel_grid.append(pix_val[i:i+image_width-1])
    i += image_width

if bw:
    for row in pixel_grid:
        for i in range(len(row)):
            sum = 0
            count = 0
            for j in range(len(row[i])):
                sum += row[i][j]
                count += 1
            row[i] = sum//count

file = open(file_out, "w")

for i in range(len(pixel_grid)):
    for j in range(len(pixel_grid[i])):
        file.write(str(pixel_grid[i][j]))
        if j != len(pixel_grid[i])-1:
            file.write(" ")
    if i != len(pixel_grid)-1:
        file.write("\n")

file.close()
