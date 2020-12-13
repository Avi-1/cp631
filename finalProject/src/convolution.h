#ifndef CONVOLUTION_H
#define CONVOLUTION_H

int apply_convolution(Matrix* kernel_x, Matrix* kernel_y, Matrix* image, int i, int j);

Matrix* process_image(Matrix* kernel_x, Matrix* kernel_y, Matrix* image);

#endif
