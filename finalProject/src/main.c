#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"

int main(int argc, char* argv[]){
    char *kern, *img, *output;
    Matrix *kernel, *image, *final;

    kern = argv[1];
    img = argv[2];
    output = argv[3];

    kernel = get_matrix_from_file(kern);
    image = get_matrix_from_file(img);
    final = process_image(kernel, image);

    write_matrix_to_file(output, final);

    return 0;
}
