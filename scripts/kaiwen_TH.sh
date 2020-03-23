#!/bin/bash
yhrun -n 24 -N 1 -p work ./mpi_sum 1000000000
yhrun -c 24 -n 1 -p work ./omp_with_lock 24 100000

