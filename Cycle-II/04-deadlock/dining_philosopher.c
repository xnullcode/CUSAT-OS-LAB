#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // Number of philosophers

pthread_t philosopher[N];
sem_t fork_sem[N];

void* philosopher_func(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking\n", id);

    // WAIT operation
    sem_wait(&fork_sem[left]);
    sem_wait(&fork_sem[right]);

    // Critical section (Eating)
    printf("Philosopher %d is eating\n", id);
    sleep(1);

    // SIGNAL operation
    sem_post(&fork_sem[right]);
    sem_post(&fork_sem[left]);

    printf("Philosopher %d finished eating and returns to thinking\n", id);

    return NULL;
}

int main() {
    int i;
    int id[N];

    // Initialize synchronization mechanism (forks available)
    for (i = 0; i < N; i++) {
        sem_init(&fork_sem[i], 0, 1);
    }

    printf("Creating philosopher threads...\n");

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&philosopher[i], NULL, philosopher_func, &id[i]);
    }

    // Wait for all philosophers to finish
    for (i = 0; i < N; i++) {
        pthread_join(philosopher[i], NULL);
    }

    // Release synchronization resources
    for (i = 0; i < N; i++) {
        sem_destroy(&fork_sem[i]);
    }

    printf("Dining Philosopher execution completed.\n");
    return 0;
}
