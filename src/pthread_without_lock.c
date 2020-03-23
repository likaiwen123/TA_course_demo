#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct thread_arg {
    int multiplication;
    int* val;
} thread_arg;

void* work(void *arg) {
    thread_arg* args = (thread_arg*)arg;
    int multiplication = args->multiplication;
    int *val = args->val;
    for (int i = 0; i < multiplication; ++i) {
        *val += 1;
    }
}

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

    pthread_t* tid = (pthread_t *)malloc(sizeof(pthread_t) * nThreads);

    // 2. Main body
    int val = 0;

    // omp_set_dynamic(0); 
    // omp_set_num_threads(nThreads);
    int index = 0;

    thread_arg args;
    args.multiplication = multiplication;
    args.val = &val;

    while (index < nThreads) {
        int err = pthread_create(&tid[index], NULL, &work, (void*)&args);
        if (err != 0) {
            printf("Thread can not be created！ Error Code [%d]\n", err);
        }
        ++index;
    }
    for (int i = 0; i < nThreads; ++i) {
        pthread_join(tid[i], NULL);
    }

    printf("val should be %d, and actually val is %d.\n", nThreads * multiplication, val);

    // 3. Finalize and Return
    free(tid);
    return 0;
}
