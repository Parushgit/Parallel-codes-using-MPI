#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>
#include <iostream>
using namespace std;

// Creates an array of random numbers. Each number has a value from 0 - 1
float *create_rand_nums(int num_elements) {
    float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++) {
      rand_nums[i] = (rand() / (float)RAND_MAX);
    }
    return rand_nums;
  }

// Computes the average of an array of numbers
float compute_avg(float *array, int num_elements) {
    float sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
      sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char** argv) {

    cout<<"Enter the number of elements per process"<<endl;
    int num_elements_per_proc;
    cin>>num_elements_per_proc;

    int procid, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);


    float *rand_nums = NULL;
    if (procid == 0) {
      rand_nums = create_rand_nums(num_elements_per_proc * numprocs);
    }

    float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
    assert(sub_rand_nums != NULL);

    MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums, num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Compute the average of your subset
    float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

    float *sub_avgs = NULL;
    if (procid == 0) {
      sub_avgs = (float *)malloc(sizeof(float) * numprocs);
      assert(sub_avgs != NULL);
    }

    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);



    if (procid == 0) {
        float avg = compute_avg(sub_avgs, numprocs);
        printf("Avg of all elements is %f\n", avg);
        // Compute the average across the original data for comparison
        float original_data_avg =
          compute_avg(rand_nums, num_elements_per_proc * numprocs);
        printf("Avg computed across original data is %f\n", original_data_avg);
      }


    // Clean up
  if (procid == 0) {
    free(rand_nums);
    free(sub_avgs);
  }
  free(sub_rand_nums);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}