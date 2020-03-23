#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // 1. Initialization

    int nThreads = 0;
    int multiplication = 100;

    if (argc > 2) {
        nThreads = atoi(argv[1]);
        multiplication = atoi(argv[2]);
    }
    else if (argc > 1){
        nThreads = atoi(argv[1]);
        multiplication = 100;
    }
    else {
        nThreads = 4;
        multiplication = 100;
    }
    printf("Number of threads: %d\n", nThreads);
    printf("Multiplication factor: %d\n", multiplication);

    // 2. Main body
    int val = 0;

    omp_set_dynamic(0); 
    omp_set_num_threads(nThreads);

#pragma omp parallel
{
    for (int i = 0; i < multiplication; ++i) {
// #pragma omp atomic
        val += 1;
    }
}

    printf("val should be %d, and actually val is %d.\n", nThreads * multiplication, val);

    // 3. Finalize and Return
    return 0;
}
