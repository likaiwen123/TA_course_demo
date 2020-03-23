#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double process(int val) {
    return log((double)(val + 1));
}

int main(int argc, char** argv) {
    // 1. Initialization
    MPI_Init(NULL, NULL);

    int size = 1;
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max = 0;
    if (argc > 1) {
        max = atoi(argv[1]);
    }
    else{
        max = 100;
    }

    // 2. Main body
    // 2.1 Distribute tasks
    int num = max / size;
    int res = max % size;

    int lower = 0;
    int upper = max;
    if (rank < res) {
        lower = rank * num + rank;
        upper = lower + num + 1;
    }
    else {
        lower = rank * num + res;
        upper = lower + num;
    }

    printf("Proc %d: [%d, %d)\n", rank, lower, upper);

    // 2.2 Do the calculation and reduce the result
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    double partialSum = 0.0;
    for (int i = lower; i < upper; ++i) {
        partialSum += process(i);
    }

    double sum = 0.0;
    MPI_Allreduce(&partialSum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        printf("\nProc %d gives the result as %8.4lf.\n", rank, sum);
        printf("Time used: %8.2lfs\n", end - start);
    }

    // 3. Finalize and Return
    MPI_Finalize();
    return 0;
}
