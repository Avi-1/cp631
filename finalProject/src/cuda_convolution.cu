extern "C" { 
    #include "matrix.h"
    #include "basic_functions.h"
    #include "file_io.h"
    #include "convolution.h"
}
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__global__ void apply_sobel_convolution_cuda(int *kernel_x, int *kernel_y, int *image, int*output, int kernel_x_dim, int image_height, int image_width){
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int index = row * image_width + col;
    if( row <= image_height && col <= image_width){
        int gradient_magnitude, border = kernel_x_dim/2;
        int convolution_sum_x = 0, convolution_sum_y = 0;

        if(row < 1 || col < 1 || row > image_height-border-1 || col > image_width-1){
            output[index] = 255; // Ignore the border
        } else {
            int i, j;
            // Apply x
            for(i = 0-border; i <= border; i++){
                for(j = 0-border; j <= border; j++){
                    convolution_sum_x += kernel_x[(i+border) * kernel_x_dim + j+border] * image[(row+i)*image_width + col+j];
                }
            }

            // Apply y
            for(i = 0-border; i <= border; i++){
                for(j = 0-border; j <= border; j++){
                    convolution_sum_y += kernel_y[(i+border) * kernel_x_dim + j+border] * image[(row+i)*image_width + col+j];
                }
            }

            gradient_magnitude = convolution_sum_x + convolution_sum_y;
            if(gradient_magnitude > 255) gradient_magnitude = 255;
            if(gradient_magnitude < 0) gradient_magnitude = 0;
            output[index] = 255 - gradient_magnitude;
        }
    }
}

int apply_sobel_convolution (Matrix* kernel_x, Matrix* kernel_y, Matrix* image, int x, int y){
    
    int gradient_magnitude, border = kernel_x->width / 2;
    int convolution_sum_x = 0, convolution_sum_y = 0;
    int i, j;
        

    if(x < 1 || y < 1 || x > image->height-border-1 || y > image->width-border-1){
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
    
    gradient_magnitude = convolution_sum_x + convolution_sum_y;
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

    printf("Image width = %d height= %d. \n", image->width, image->height);
    printf("Kernel X width = %d height= %d. \n", kernel_x->width, kernel_x->height);
    printf("Kernel Y width = %d height= %d. \n", kernel_y->width, kernel_y->height);

    int i,j;
    for(i=0; i<image->height; i++){
        for(j=0; j<image->width; j++){
            set_value(convoluted_matrix, i, j, apply_sobel_convolution(kernel_x, kernel_y, image, i, j));
        }
    }

    write_matrix_to_file("../data/test_o.txt", convoluted_matrix);
    printf("Done: Output @ ../data/test_o.txt\n");

    int temp[image->height][ image->width];
    int shadow[image->height][ image->width];

    int *image_gpu;
    int *convoluted_image_gpu;
    int *kernel_x_gpu;
    int *kernel_y_gpu;

    size_t image_size = image->width * image->height * sizeof(int);
    size_t kernel_size  = kernel_x->width * kernel_x->height * sizeof(int);

    cudaMalloc((void **) &image_gpu, image_size);
    cudaMalloc((void **) &convoluted_image_gpu, image_size);
    cudaMalloc((void **) &kernel_x_gpu, kernel_size);
    cudaMalloc((void **) &kernel_y_gpu, kernel_size);

    cudaMemcpy(image_gpu, image->array, image_size, cudaMemcpyHostToDevice);
    cudaMemcpy(convoluted_image_gpu, temp, image_size, cudaMemcpyHostToDevice);
    cudaMemcpy(kernel_x_gpu, kernel_x->array, kernel_size, cudaMemcpyHostToDevice);
    cudaMemcpy(kernel_y_gpu, kernel_x->array, kernel_size, cudaMemcpyHostToDevice);

    int blocks = sqrt((2 * image->height * image->width) / 1024);
    dim3 blocksPerGrid(blocks, blocks, 1);
    dim3 threadsPerGrid(32, 32, 1);
    apply_sobel_convolution_cuda<<<blocksPerGrid, threadsPerGrid>>>(kernel_x_gpu, kernel_y_gpu, image_gpu, convoluted_image_gpu, kernel_x->width, image->height, image->width);

    cudaMemcpy(shadow, convoluted_image_gpu, image_size, cudaMemcpyDeviceToHost);


    cudaDeviceSynchronize();
    if(cudaError_t error = cudaGetLastError()){
      printf ("Error detected after kernel %d\n", error);
      exit (error);
    }

    write_array_to_file("../data/test_gpu.txt", &shadow[0][0], image->height, image->width);

    printf("GPU Done: Output @ ../data/test_gpu.txt\n");

    return 0;
}
