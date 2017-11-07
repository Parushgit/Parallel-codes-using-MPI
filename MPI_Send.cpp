#include<iostream>
#include<mpi.h>
#include<stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
    int ierr, procid, numprocs;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    if(numprocs != 2)
    {
        cout<<"Number of processors are not 2"<<endl;
        return MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if(procid == 0)
    {
        double pi = 3.14;
        ierr = MPI_Send(&pi, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        //MPI_Send(&pi, 1, MPI_DOUBLE, 1, 111, MPI_COMM_WORLD);
        // if(ierr == MPI_SUCCESS)
        // cout<<"Successful"<<procid<<endl;
        // else 
        // cout<<"Unsuccessful"<<endl;
        cout<<"Process ID "<<procid<<" sent value "<<pi<<" to 1."<<endl;
    }
    if(procid == 1)
    {
        double buf;
        MPI_Status status;
        ierr = MPI_Recv(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        //MPI_Recv(&buf, 1, MPI_DOUBLE, 0, 111, MPI_COMM_WORLD, &status);
        if(ierr == MPI_SUCCESS)
        cout<<"Message "<<buf<<" received for "<<procid<<endl;
        else 
        cout<<"Unsuccessful"<<endl;
    }

    //cout<<"Hello world! I am process "<<procid<<" out of "<<numprocs<<endl;
    ierr = MPI_Finalize();
    return 0;
}
//mpirun -n 10 -mca btl ^openib ./helloworld_mpi 
//mpic++ helloworld_mpi.cpp -std=c++11 -o helloworld_mpi