#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int p, my_rank, q;
    MPI_Comm grid_comm;
    int dim_sizes[2];
    int wrap_around[2];
    int coordinates[2];
    int free_cords[2];
    int reorder = 1;
    int my_grid_rank, grid_rank;
    int row_test, col_test;
    MPI_Comm row_comm;
    MPI_Comm col_comm;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    q = (int) sqrt((double)p);
    dim_sizes[0] = dim_sizes[1] = q;
    wrap_around[0] = wrap_around[1] = 1;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim_sizes, wrap_around, reorder, &grid_comm);
    MPI_Comm_rank(grid_comm, &my_grid_rank);
    MPI_Cart_coords(grid_comm, my_grid_rank, 2, coordinates);
    MPI_Cart_rank(grid_comm, coordinates, &grid_rank);
    cout<<"Process "<<my_rank<<"> my_grid_rank = "<<my_grid_rank<<"coords = ("<<coordinates[0]<<","<<coordinates[1]<<"), grid_rank = "<<grid_rank<<endl;
    free_cords[0] = 0;
    free_cords[1] = 1;
    MPI_Cart_sub(grid_comm, free_cords, &row_comm);

    if(coordinates[0] == 0)
    row_test = coordinates[i];
    else 
    row_test = -1;

    MPI_Bcast(&row_test, 1, MPI_INT, 0, row_comm);
    printf("Process %d > coords = (%d, %d), row_test = %d\n", my_rank, coordinates[0], coordinates[1], row_test);


    free_cords[0] = 0;
    free_cords[1] = 1;
    MPI_Cart_sub(grid_comm, free_cords, &col_comm);

    if(coordinates[0] == 0)
    col_test = coordinates[i];
    else 
    col_test = -1;

    MPI_Bcast(&row_test, 1, MPI_INT, 0, col_comm);
    printf("Process %d > coords = (%d, %d), col_test = %d\n", my_rank, coordinates[0], coordinates[1], col_test);

    MPI_Finalize();
    return 0;

}