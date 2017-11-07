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

    if(numprocs % 2 != 0)
    {
        cout<<"Number of processors are not 2"<<endl;
        return MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if(procid % 2 == 0)
    {
        double pi = 3.14 + procid;
        ierr = MPI_Send(&pi, 1, MPI_DOUBLE, procid+1, 111, MPI_COMM_WORLD);
        cout<<"Process ID "<<procid<<" sent value "<<pi<<" to "<<procid+1<<"."<<endl;
    }
    if(procid % 2 == 1)
    {
        //cout<<"Inside RECV"<<endl;
        double buf;
        MPI_Status status;
        ierr = MPI_Recv(&buf, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 111, MPI_COMM_WORLD, &status);
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
//mpirun -n 10 -mca btl ^openib ./MPI_MultipleSend 
//mpic++ MPI_MultipleSend.cpp -std=c++11 -o MPI_MultipleSend