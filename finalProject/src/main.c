#include<stdlib.h>
#include<stdio.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"
#include"mpi.h"

int main(int argc, char* argv[]){
    //initialize variables needed
    char *kern, *img, *output;
    Matrix *kernel, *image, *local_image, *final, *local_final;
    int my_rank, p, kheight, kwidth, iheight, iwidth;
    MPI_Status *status;

    //set file names for io
    kern = argv[1];
    img = argv[2];
    output = argv[3];

    //start up MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &p);

    //ingest matrices from file on process 0, calculate the dimensions of
    //matrices needed for each process and create local matrix
    if(my_rank == 0){
      kernel = get_matrix_from_file(kern);
      image = get_matrix_from_file(img);
      kheight = kernel->height;
      kwidth = kernel->width;
      iheight = image->height/p + (kheight/2);
      iwidth = image->width;
      local_image = create_matrix(image->height/p, iwidth);
    }

    //broadcast dimension information to all other processes
    MPI_Bcast(&kheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&kwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //other processes initialize relevant matrices
    if(my_rank != 0){
      kernel = create_matrix(kheight, kwidth):
      local_image = create_matrix(iheight, iwidth);
    }

    //broadcast kernel so every process has a copy
    MPI_Bcast(kernel.array, kheight*kwidth, MPI_INT, 0, MPI_COMM_WORLD);

    //copy image portion into local matrix and send image slices out to other
    //processes
    if(my_rank == 0){
      for(int i=0; i<local_image->height; i++){
        for(int j=0; j<local_image->width; j++){
          set_value(local_image, i, j, get_value(image, i, j));
        }
      }
      int index = (iheight-1) * iwidth;
      for(int i=1; i<p; i++){
        MPI_Send(&image->array[index], iheight*iwidth, MPI_INT, i, 0, MPI_COMM_WORLD);
        index += iheight * iwidth;
      }
    } else{}
      MPI_Recv(local_image.array, iheight*iwidth, MPI_INT, 0, 0, MPI_COMM_WORLD, status);
    }

    //calculate local final portion after applying the convolution
    local_final = process_image(kernel, local_image);

    //still need to gather finished portions into the final matrix and instantiate
    //the final matrix to write, or write it peicemeal from each process.
    
    MPI_Finalize();

    write_matrix_to_file(output, final);

    return 0;
}
