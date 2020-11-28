#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int get_value(Matrix* m, int i, int j){
  return m->array[i*m->width + j];
}

void set_value(Matrix* m, int i, int j, int v){
  m->array[i*m->width + j] = v;
}

void initialize_array(Matrix* m){
  m->array = malloc(m->height*m->width*sizeof(int));
}

void free_array(Matrix* m){
  free(m->array);
}

Matrix* create_matrix(int w, int h){
  Matrix* m = malloc(sizeof(Matrix));
  if (m == NULL) {
    return NULL;
  }
  m->width = w;
  m->height = h;
  initialize_array(m);
  return m;
}

void free_matrix(Matrix* m){
  free_array(m);
  free(m);
}
