#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"

__global__ void apply_sobel_convolution_cuda(int *kernel_x, int *kernel_y, int *image, int*output, int *kernel_x_dim, int *image_dim_x, int *image_dim_y){
    
}

int apply_sobel_convolution (Matrix* kernel_x, Matrix* kernel_y, Matrix* image, int x, int y){
    
    int kernel_sum = 0, border = kernel_x->width / 2;
    int convolution_sum_x = 0, convolution_sum_y = 0;
    int i, j;
        

    if(x < 0 || y < 0 || x == image->width-border || y == image->height-border){
        return 0; // Ignore the border
    }

    // Apply x
    for(i = 0-border; i <= border; i++){
        for(j = 0-border; j <= border; j++){
            convolution_sum_x += get_value(kernel_x, i+border, j+border) * get_value(image, x+i, y+j);
        }
    }

    // Apply y
    for(i = 0-border; i <= border; i++){
        for(j = 0-border; j <= border; j++){
            convolution_sum_y += get_value(kernel_y, i+border, j+border) * get_value(image, x+i, y+j);
        }
    }

    int gradient_magnitude = convolution_sum_x + convolution_sum_y;
    if(gradient_magnitude > 255) gradient_magnitude = 255;
    if(gradient_magnitude < 0) gradient_magnitude = 0;
    return 255 - gradient_magnitude;
}


int main(int argc, char* argv[]){
    Matrix *kernel_x, *kernel_y, *image, *convoluted_matrix;

    kernel_x = get_matrix_from_file("../data/kernel_x.txt");
    kernel_y = get_matrix_from_file("../data/kernel_y.txt");
    image = get_matrix_from_file("../data/imgbw.txt");
    
    convoluted_matrix = create_matrix(image->height, image->width);

    for(int i=0; i<image->height; i++){
        for(int j=0; j<image->width; j++){
            set_value(convoluted_matrix, i, j, apply_sobel_convolution(kernel_x, kernel_y, image, i, j));
        }
    }

    write_matrix_to_file("../data/test_o.txt", convoluted_matrix);
    printf("Done\n");
    return 0;
}
