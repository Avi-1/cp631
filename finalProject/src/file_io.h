#ifndef FILE_IO_H
#define FILE_IO_H

int* get_dimensions(char* file_name);

Matrix* get_matrix_from_file(char* file_name);

void write_matrix_to_file(char* file_name, Matrix* matrix);

#endif
