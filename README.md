# Sobel Edge Detection using MPI and CUDA
## Group 2 - Final Project

### Usage

+ *Convert image to text file using Python*
+ *python3*  *imageExtraction.py*  *input_image*  *output_text*  *image_width* *colour_image*

> `cd Python`

> `python3 imageExtraction.py ../finalProject/data/einstein.jpg ../finalProject/data/einstein.txt 496 true`

+ *Compile CUDA/MPI code using Makefile*
+ *Run convolution*
+ *./cuda_main.x*  *horizontal_kernel*  *vertical_kernel*  *input_text*  *output text*

> `cd ../finalProject`

> `make -f Makefile cuda_full_program`

> `cd ../build`

> `./cuda_main.x ../data/kernel_horizontal_edge_detect_3x3.mat ../data/kernel_vertical_edge_detect_3x3.mat ../data/einstein.txt ../data/einstein-output.txt`

+ *View text as image using Python*
+ *python3*  *viewImageFromText.py*  *input_text*

> `cd ../../Python`

> `python3 viewImageFromText.py ../finalProject/data/einstein-output.txt`
