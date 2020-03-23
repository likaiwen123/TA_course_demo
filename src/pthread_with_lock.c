#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t lock;

typedef struct thread_arg {
    int multiplication;
    int* val;
} thread_arg;

void* work(void *arg) {
    thread_arg* args = (thread_arg*)arg;
    int multiplication = args->multiplication;
    int *val = args->val;
    for (int i = 0; i < multiplication; ++i) {
        pthread_mutex_lock(&lock);
        *val += 1;
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc, char** argv) {
    // 1. Initialization
    // 1.1 Number of Threads and multiplication factor initialization

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

    // 1.2 Thread ID Initialization
    pthread_t* tid = (pthread_t *)malloc(sizeof(pthread_t) * nThreads);

    // 1.3 Lock Initialization
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("mutex initialization failed!\n");
        return 1;
    }

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
    pthread_mutex_destroy(&lock);
    return 0;
}
