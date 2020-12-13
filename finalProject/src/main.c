#include<stdlib.h>
#include<stdio.h>
#include <time.h>
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

    clock_t start = clock();
    kernel_x = get_matrix_from_file(kern_x);
    kernel_y = get_matrix_from_file(kern_y);
    image = get_matrix_from_file(img);
    final = process_image(kernel_x, kernel_y, image);

    float time_spent = (float)(clock() - start) / CLOCKS_PER_SEC;
    printf("Serial code Done in %f seconds.\n", time_spent);
    log_timing("serial", kernel_x->width, time_spent);
    
    write_matrix_to_file(output, final);

    return 0;
}
