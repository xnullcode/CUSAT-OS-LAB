#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int x = 0; 
sem_t sem_p; 

void* thread1_func(void* arg) {
    printf("Thread 1 started...\n");
    sem_wait(&sem_p); 

    printf("Thread 1: Current value of x is %d\n", x);
    x = x + 1;
    printf("Thread 1: New value of x is %d\n", x);

    sem_post(&sem_p); 
    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2 started...\n");
    int y; 

    sem_wait(&sem_p); 

    y = x; 
    printf("Thread 2: Copied x to y. y = %d, x = %d\n", y, x);

    x = x + 1;
    printf("Thread 2: Incremented x. New x = %d\n", x);

    sem_post(&sem_p); 
    return NULL;
}

void* thread3_func(void* arg) {
    printf("Thread 3 (Decrementing thread) started...\n");

    sem_wait(&sem_p);

    printf("Thread 3: Current value of x is %d\n", x);
    x = x - 1;
    printf("Thread 3: Decremented x. New value of x is %d\n", x);

    sem_post(&sem_p);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3; 

    if (sem_init(&sem_p, 0, 1) == -1) {
        perror("Semaphore initialization failed");
        exit(1);
    }

    printf("Main: Semaphore initialized. Creating threads...\n");

    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);
    pthread_create(&t3, NULL, thread3_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Main: All threads completed. Final value of x: %d\n", x);

    sem_destroy(&sem_p);
    return 0;
}
