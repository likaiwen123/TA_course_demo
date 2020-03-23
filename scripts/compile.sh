#!/bin/bash
gcc -pthread ../src/pthread_with_lock.c -o pthread_with_lock -std=gnu11
gcc -pthread ../src/pthread_without_lock.c -o pthread_without_lock -std=gnu11
gcc -fopenmp ../src/omp_without_lock.c -o omp_without_lock -std=gnu11
gcc -fopenmp ../src/omp_with_lock.c -o omp_with_lock -std=gnu11
mpicc -o mpi_sum ../src/mpi_sum.c -lm -std=gnu11
mpicc -o mpi_round ../src/mpi_round.c -std=gnu11

