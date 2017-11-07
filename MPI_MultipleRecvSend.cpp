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

    if(procid != 0)
    {
        double pi = -procid;
        ierr = MPI_Send(&pi, 1, MPI_DOUBLE, 0, 111, MPI_COMM_WORLD);
        cout<<"Process ID "<<procid<<" sent value "<<pi<<" to 0."<<endl;
    }
    if(procid  == 0)
    {
        //cout<<"Inside RECV"<<endl;
        double sum = 0.0;
        double buf;
        MPI_Status status;
        int counter = 0;
        while(counter < numprocs - 1)
        {
            ierr = MPI_Recv(&buf, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 111, MPI_COMM_WORLD, &status);
            sum = sum + buf;
            if(ierr == MPI_SUCCESS)
            cout<<"Message "<<buf<<" received for "<<procid<<endl;
            else 
            MPI_Abort(MPI_COMM_WORLD, 1);
            counter++;
        }
        cout<<"Total Sum is : "<<sum<<endl;//" received for "<<procid<<endl;
    }
    ierr = MPI_Finalize();
    return 0;
}
//mpirun -n 10 -mca btl ^openib ./MPI_MultipleRecvSend 
//mpic++ MPI_MultipleRecvSend.cpp -std=c++11 -o MPI_MultipleRecvSend