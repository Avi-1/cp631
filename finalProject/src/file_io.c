#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "basic_functions.h"

//char fileName[100];
//FILE *file;

//file = fopen(fileName, "r+");

//fscanf(file, "%f", &temp_matrix[i][j]);
//fclose(file);

int* get_dimensions(FILE* fp){
  int c = 0;
  int row = 0;
  int col = 0;
  int* d = malloc(2*sizeof(int));

  while ((c = getc(fp)) != EOF){
    if (c == '\n') row++;
    else if (c == ' ' && row == 0) col++;
  }
  d[0] = row;
  d[1] = col + 1;
  return d;
}
