#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "basic_functions.h"

int* get_dimensions(char* file_name){
  FILE* fp;
  fp = fopen(file_name, "r+");
  int c = 0;
  int row = 0;
  int col = 0;
  int* d = malloc(2*sizeof(int));

  while ((c = getc(fp)) != EOF){
    if (c == '\n') row++;
    else if (c == ' ' && row == 0) col++;
  }
  fclose(fp);
  d[0] = row;
  d[1] = col + 1;
  return d;
}

Matrix* get_matrix_from_file(char* file_name){
  FILE* file;

  int* dimensions = get_dimensions(file_name);
  file = fopen(file_name, "r+");
  Matrix* matrix = create_matrix(dimensions[0], dimensions[1]);
  for(int i=0; i<matrix->height; i++){
    for(int j=0; j<matrix->width; j++){
      int value;
      fscanf(file, "%d", &value);
      set_value(matrix, i, j, value);
    }
  }
  fclose(file);
  return matrix;
}
