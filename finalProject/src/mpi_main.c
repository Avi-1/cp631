#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include <time.h>
#include"matrix.h"
#include"basic_functions.h"
#include"file_io.h"
#include"convolution.h"


int main(int argc, char* argv[]){
    //initialize variables needed
    char *kern_x, *kern_y, *img, *output;
    Matrix *kernel_x, *kernel_y, *image, *final, *local_image, *local_final;
    int my_rank, p, kheight, kwidth, iheight, iwidth, block_size, i, j;
    MPI_Status *status;
    clock_t start;

    kernel_x = NULL;
    kernel_y = NULL;
    image = NULL;
    final = NULL;
    local_image = NULL;
    local_final = NULL;
    //set file names for io
    kern_x = argv[1];
    kern_y = argv[2];
    img = argv[3];
    output = argv[4];

    //start up MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &p);

    //ingest matrices from file on process 0, calculate the dimensions of
    //matrices needed for each process and create local matrix
    if(my_rank == 0){
      kernel_x = get_matrix_from_file(kern_x);
      kernel_y = get_matrix_from_file(kern_y);
      image = get_matrix_from_file(img);
      final = create_matrix(image->height, image->width);
      kheight = kernel_x->height;
      kwidth = kernel_x->width;
      iheight = image->height/p;
      iwidth = image->width;
      local_image = create_matrix(iheight, iwidth);
    }

    //broadcast dimension information to all other processes
    MPI_Bcast(&kheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&kwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iheight, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&iwidth, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //other processes initialize relevant matrices problem is in the matrix initialization
    if(my_rank != 0){
      kernel_x = create_matrix(kheight, kwidth);
      kernel_y = create_matrix(kheight, kwidth);
      local_image = create_matrix(iheight + (kheight-1), iwidth);
    }

    //broadcast kernel_x so every process has a copy
    MPI_Bcast(kernel_x->array, kheight*kwidth, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(kernel_y->array, kheight*kwidth, MPI_INT, 0, MPI_COMM_WORLD);

    //copy image portion into local matrix and send image slices out to other
    //processes
    if(my_rank == 0){
      for(i=0; i<local_image->height; i++){
        for(j=0; j<local_image->width; j++){
          set_value(local_image, i, j, get_value(image, i, j));
        }
      }
      int index = (iheight-(kheight-1)) * iwidth;
      block_size = (iheight+(kheight-1)) * iwidth;
      for(i=1; i<p; i++){
        MPI_Send(&image->array[index], block_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        index += iheight*iwidth;
      }
    } else{
      MPI_Recv(local_image->array, (iheight+(kheight-1))*iwidth, MPI_INT, 0, 0, MPI_COMM_WORLD, status);
    }

    if(my_rank == 0){
      start = clock();
    }
    //calculate local final portion after applying the convolution
    local_final = process_image(kernel_x, kernel_y, local_image);

    MPI_Barrier(MPI_COMM_WORLD);
    if(my_rank == 0){
      float time_spent = (float)(clock() - start) / CLOCKS_PER_SEC;
      printf("MPI code Done in %f seconds.\n", time_spent);
      log_timing("MPI", kernel_x->width, time_spent);
    }

    //gather finished portions of the final matrix back into the complete final
    //for file output
    if(my_rank == 0){
      for(i=0; i<local_image->height; i++){
        for(j=0; j<local_image->width; j++){
          set_value(final, i, j, get_value(local_final, i, j));
        }
      }
      int index = (local_final->height-(kheight-1)) * local_final->width;
      block_size = (iheight+kheight/2)*iwidth;
      for(i=1; i<p; i++){
        MPI_Recv(&final->array[index], block_size, MPI_INT, i, 0, MPI_COMM_WORLD, status);
        index += iheight*iwidth;
      }
    } else{
      block_size = (iheight+kheight/2)*iwidth;
      MPI_Send(&local_final->array[local_final->width*(kheight/2)], block_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if(my_rank == 0){
      write_matrix_to_file(output, final);
    }

    MPI_Finalize();

    return 0;
}
