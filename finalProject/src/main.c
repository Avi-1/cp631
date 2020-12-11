#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"

int main(int argc, char* argv[]){
    char *kern, *img, *output;
    Matrix *kernel, *image, *final;
    int my_rank, p, kheight, kwidth, iheight, iwidth;

    kern = argv[1];
    img = argv[2];
    output = argv[3];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(my_rank == 0){
      kernel = get_matrix_from_file(kern);
      image = get_matrix_from_file(img);
      kheight = kernel->height;
      kwidth = kernel->width;
      iheight = image->height;
      iwidth = image->width;
    }

    MPI_Bcast(&kheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&kwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(my_rank != 0){
      kernel = create_matrix(kheight, kwidth):
      image = create_matrix(iheight, iwidth);
    }

    MPI_Bcast(kernel.array, kheight*kwidth, MPI_INT, 0, MPI_COMM_WORLD);

    final = process_image(kernel, image);

    MPI_Finalize();

    write_matrix_to_file(output, final);

    return 0;
}
