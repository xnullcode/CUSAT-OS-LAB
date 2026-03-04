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

    while (1) {  // Infinite loop to make philosophers think and eat repeatedly
        printf("Philosopher %d is thinking\n", id);
        sleep(2);  // Simulate thinking time (change as needed)

        // Avoid deadlock by reversing fork pickup order for one philosopher (last philosopher)
        if (id == N - 1) {
            int temp = left;
            left = right;
            right = temp;
        }

        // WAIT operation
        sem_wait(&fork_sem[left]);
        sem_wait(&fork_sem[right]);

        // Critical section (Eating)
        printf("Philosopher %d is eating\n", id);
        sleep(1);  // Simulate eating time (change as needed)

        // SIGNAL operation
        sem_post(&fork_sem[right]);
        sem_post(&fork_sem[left]);

        printf("Philosopher %d finished eating and returns to thinking\n", id);
    }

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

    // Wait for all philosophers to finish (which never happens due to the infinite loop)
    for (i = 0; i < N; i++) {
        pthread_join(philosopher[i], NULL);
    }

    // Release synchronization resources (although this part won't be reached)
    for (i = 0; i < N; i++) {
        sem_destroy(&fork_sem[i]);
    }

    printf("Dining Philosopher execution completed.\n");
    return 0;
}
