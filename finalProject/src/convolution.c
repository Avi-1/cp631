#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "basic_functions.h"

//apply convolution to a single part of the image matrix
int apply_convolution(Matrix *kernel_x, Matrix *kernel_y, Matrix *image, int x, int y)
{
  int gradient_magnitude, border = kernel_x->width / 2;
  int convolution_sum_x = 0, convolution_sum_y = 0;
  int i, j;

  if (x < 1 || y < 1 || x > image->height - border - 1 || y > image->width - border - 1)
  {
    return 0; // Ignore the border
  }

  // Apply x
  for (i = 0 - border; i <= border; i++)
  {
    for (j = 0 - border; j <= border; j++)
    {
      convolution_sum_x += get_value(kernel_x, i + border, j + border) * get_value(image, x + i, y + j);
    }
  }

  // Apply y
  for (i = 0 - border; i <= border; i++)
  {
    for (j = 0 - border; j <= border; j++)
    {
      convolution_sum_y += get_value(kernel_y, i + border, j + border) * get_value(image, x + i, y + j);
    }
  }

  gradient_magnitude = convolution_sum_x + convolution_sum_y;
  if (gradient_magnitude > 255)
    gradient_magnitude = 255;
  if (gradient_magnitude < 0)
    gradient_magnitude = 0;
  return 255 - gradient_magnitude;
}

//apply convolution to the entire image matrix
Matrix *process_image(Matrix *kernel_x, Matrix *kernel_y, Matrix *image)
{
  Matrix *convoluted_matrix = create_matrix(image->height, image->width);

  clock_t start = clock();
  int i, j;
  for (i = 0; i < convoluted_matrix->height; i++)
    for (j = 0; j < convoluted_matrix->width; j++)
      set_value(convoluted_matrix, i, j, apply_convolution(kernel_x, kernel_y, image, i, j));

  float time_spent = (float)(clock() - start) / CLOCKS_PER_SEC;
  printf("Serial code Done in %f seconds.\n", time_spent);
  log_timing("serial", kernel_x->width, time_spent);

  return convoluted_matrix;
}
