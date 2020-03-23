#!/bin/bash
gcc -pthread pthread_with_lock.c -o pthread_with_lock -std=gnu11
gcc -pthread pthread_without_lock.c -o pthread_without_lock -std=gnu11
gcc -fopenmp omp_without_lock.c -o omp_without_lock -std=gnu11
gcc -fopenmp omp_with_lock.c -o omp_with_lock -std=gnu11
mpicc -o mpi_sum mpi_sum.c -lm -std=gnu11
mpicc -o mpi_round mpi_round.c -std=gnu11

