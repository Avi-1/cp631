#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "basic_functions.h"

int apply_convolution(Matrix* kernel, Matrix* image, int i, int j){
  int sum = 0;
  for(int x=0; x<kernel->height; x++)
    for(int y=0; y<kernel->width; y++)
      sum += get_value(kernel, x, y) * get_value(image, x+i, y+j);
  return sum;
}

Matrix* process_image(Matrix* kernel, Matrix* image){
  int conv_height = image->height - (kernel->height/2);
  int conv_width = image->width - (kernel->width/2);

  Matrix* convoluted_matrix = create_matrix(conv_height, conv_width);

  for(int i=0; i<convoluted_matrix->height; i++)
    for(int j=0; j<convoluted_matrix->width; j++)
      set_value(convoluted_matrix, i, j, apply_convolution(kernel, image, i, j));

  return convoluted_matrix;
}
