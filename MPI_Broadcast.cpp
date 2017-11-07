#include<stdio.h>
#include<iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char *argv[])
{
    int ierr, procid, numprocs;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    
    float a_ptr, b_ptr; int n_ptr;

    if(procid ==0)
    {
        cout<<"Enter a, b and n"<<endl;
        cin>>a_ptr>>b_ptr>>n_ptr;
    }
    MPI_Bcast(&a_ptr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b_ptr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_ptr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(procid != 0)
    {
        cout<<"Values of a and b and n are"<<a_ptr<<"  "<<b_ptr<<"  "<<n_ptr<<endl;
    }

    ierr = MPI_Finalize();
    return 0;
}