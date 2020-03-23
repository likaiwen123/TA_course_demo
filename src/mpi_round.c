#include "mpi.h"
#include <stdio.h>

int main() {
    // 1. Initialization
    MPI_Init(NULL, NULL);

    int size = 1;
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 2. Main body

    int send = -1;
    int recv = -1;

    int src = (rank + size - 1) % size;
    int des = (rank + 1) % size;

    int tag = 100;

    MPI_Status status;

    if (rank == 0) {
        send = 0;
        MPI_Send(&send, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
        MPI_Recv(&recv, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
    }
    else {
        MPI_Recv(&recv, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
        send = recv + 1;
        MPI_Send(&send, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
    }

    printf("Proc %d sends %d to Proc %d, and receives %d from %d.\n", 
        rank, send, des, recv, src);

    // 3. Finalize and Return
    MPI_Finalize();
    return 0;
}
