#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

int get_value(Matrix* matrix, int i, int j);

void set_value(Matrix* m, int i, int j, int v);

void initialize_array(Matrix* matrix);

void free_array(Matrix* matrix);

Matrix* create_matrix(int h, int w);

void free_matrix(Matrix* m);

#endif
