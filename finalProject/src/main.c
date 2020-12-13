#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"

int main(int argc, char* argv[]){
    char *kern_x, *kern_y, *img, *output;
    Matrix *kernel_x, *kernel_y, *image, *final;

    kern_x = argv[1];
    kern_y = argv[2];
    img = argv[3];
    output = argv[4];

    kernel_x = get_matrix_from_file(kern_x);
    kernel_y = get_matrix_from_file(kern_y);
    image = get_matrix_from_file(img);
    final = process_image(kernel_x, kernel_y, image);

    write_matrix_to_file(output, final);

    return 0;
}
