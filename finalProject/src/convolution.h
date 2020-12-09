#ifndef CONVOLUTION_H
#define CONVOLUTION_H

int apply_convolution(Matrix* kernel, Matrix* image, int i, int j);

Matrix* process_image(Matrix* kernel, Matrix* image);

#endif
