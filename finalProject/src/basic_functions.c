#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
//basic functions for matrix IO to simplify the indexing math and
//create and free the matrices

int get_value(Matrix *m, int i, int j)
{
  return m->array[i * m->width + j];
}

void set_value(Matrix *m, int i, int j, int v)
{
  m->array[i * m->width + j] = v;
}

void initialize_array(Matrix *m)
{
  m->array = malloc(m->height * m->width * sizeof(int));
}

void free_array(Matrix *m)
{
  free(m->array);
}

Matrix *create_matrix(int h, int w)
{
  Matrix *m = malloc(sizeof(Matrix));

  if (m == NULL)
    return NULL;
  m->width = w;
  m->height = h;
  initialize_array(m);
  return m;
}

void free_matrix(Matrix *m)
{
  free_array(m);
  free(m);
}

void log_timing(char *implementation, int kernel_size, float time)
{
  FILE *pFile = fopen("timing_log.txt", "a");
  if (pFile == NULL)
  {
    perror("Error opening file.");
  }
  else
  {
    fprintf(pFile, "%s,%i,%f\n", implementation, kernel_size, time);
  }
  fclose(pFile);
}
