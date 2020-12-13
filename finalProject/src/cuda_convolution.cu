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
#include <time.h>

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


int main(int argc, char* argv[]){
    Matrix *kernel_x, *kernel_y, *image;
    char *kern_x, *kern_y, *img, *output;

    kern_x = argv[1];
    kern_y = argv[2];
    img = argv[3];
    output = argv[4];

    kernel_x = get_matrix_from_file(kern_x);
    kernel_y = get_matrix_from_file(kern_y);
    image = get_matrix_from_file(img);

    printf("Image width = %d height= %d. \n", image->width, image->height);
    printf("Kernel X width = %d height= %d. \n", kernel_x->width, kernel_x->height);
    printf("Kernel Y width = %d height= %d. \n", kernel_y->width, kernel_y->height);


    // int temp[image->height][ image->width];
    int shadow[image->height][ image->width];

    int *image_gpu;
    int *convoluted_image_gpu;
    int *kernel_x_gpu;
    int *kernel_y_gpu;

    size_t image_size = image->width * image->height * sizeof(int);
    size_t kernel_size  = kernel_x->width * kernel_x->height * sizeof(int);

    clock_t start = clock();
    cudaMalloc((void **) &image_gpu, image_size);
    cudaMalloc((void **) &convoluted_image_gpu, image_size);
    cudaMalloc((void **) &kernel_x_gpu, kernel_size);
    cudaMalloc((void **) &kernel_y_gpu, kernel_size);

    cudaMemcpy(image_gpu, image->array, image_size, cudaMemcpyHostToDevice);
    //cudaMemcpy(convoluted_image_gpu, temp, image_size, cudaMemcpyHostToDevice);
    cudaMemcpy(kernel_x_gpu, kernel_x->array, kernel_size, cudaMemcpyHostToDevice);
    cudaMemcpy(kernel_y_gpu, kernel_x->array, kernel_size, cudaMemcpyHostToDevice);

    int blocks = 2 * sqrt((image->height * image->width) / 1024);
    dim3 blocksPerGrid(blocks, blocks, 1);
    dim3 threadsPerGrid(32, 32, 1);
    apply_sobel_convolution_cuda<<<blocksPerGrid, threadsPerGrid>>>(kernel_x_gpu, kernel_y_gpu, image_gpu, convoluted_image_gpu, kernel_x->width, image->height, image->width);

    cudaMemcpy(shadow, convoluted_image_gpu, image_size, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();
    if(cudaError_t error = cudaGetLastError()){
      printf ("Error detected after kernel %d\n", error);
      exit (error);
    }

    float time_spent = (float)(clock() - start) / CLOCKS_PER_SEC;

    write_array_to_file(output, &shadow[0][0], image->height, image->width);

    printf("CUDA code done in %f seconds: Output %s\n", time_spent, output);
    log_timing("cuda", kernel_x->width, time_spent);

    cudaFree(image_gpu);
    cudaFree(convoluted_image_gpu);
    cudaFree(kernel_x_gpu);
    cudaFree(kernel_y_gpu);

    free_matrix(kernel_x);
    free_matrix(kernel_y);
    free_matrix(image);

    return 0;
}
