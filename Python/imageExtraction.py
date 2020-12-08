from PIL import Image

im = Image.open("/home/orthogonalstar/Pictures/rootkiss.jpg", "r")

pix_val = list(im.getdata())

pixel_grid = []

i=0
while i < len(pix_val):
    pixel_grid.append(pix_val[i:i+1919])
    i += 1920

for row in pixel_grid:
    for i in range(len(row)):
        sum = 0
        count = 0
        for j in range(len(row[i])):
            sum += row[i][j]
            count += 1
        row[i] = sum//count

file = open("/home/orthogonalstar/cp631/finalProject/data/imagebw.txt", "w")

for i in range(len(pixel_grid)):
    for j in range(len(pixel_grid[i])):
        file.write(str(pixel_grid[i][j]))
        if j != len(pixel_grid[i])-1:
            file.write(" ")
    if i != len(pixel_grid)-1:
        file.write("\n")

file.close()
