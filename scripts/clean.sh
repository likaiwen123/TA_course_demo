#!/bin/bash
cur_dir=$PWD
cd ../src/
rm mpi_sum mpi_round omp_without_lock omp_with_lock pthread_without_lock pthread_with_lock
cd $cur_dir

