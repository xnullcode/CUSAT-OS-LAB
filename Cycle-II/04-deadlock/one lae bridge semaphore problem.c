#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*
 * One Lane Bridge Problem
 * -----------------------
 * A bridge can only be crossed in one direction at a time.
 * Multiple cars from the same direction can cross simultaneously.
 * Cars from opposite directions cannot be on the bridge at the same time.
 *
 * Semaphores used:
 *   bridge     - mutual exclusion: only one direction on bridge at a time
 *   mutex_L    - protects count_L (number of left-going cars on bridge)
 *   mutex_R    - protects count_R (number of right-going cars on bridge)
 */

sem_t bridge;
sem_t mutex_L;
sem_t mutex_R;

int count_L = 0;  /* cars currently crossing Left->Right */
int count_R = 0;  /* cars currently crossing Right->Left */

void enter_bridge_left(int id) {
    sem_wait(&mutex_L);
    count_L++;
    if (count_L == 1)          /* first left car locks the bridge */
        sem_wait(&bridge);
    sem_post(&mutex_L);

    printf("  [L->R] Car %d entered bridge  (L on bridge: %d)\n", id, count_L);
}

void exit_bridge_left(int id) {
    sem_wait(&mutex_L);
    count_L--;
    printf("  [L->R] Car %d exited  bridge  (L remaining: %d)\n", id, count_L);
    if (count_L == 0)          /* last left car releases the bridge */
        sem_post(&bridge);
    sem_post(&mutex_L);
}

void enter_bridge_right(int id) {
    sem_wait(&mutex_R);
    count_R++;
    if (count_R == 1)          /* first right car locks the bridge */
        sem_wait(&bridge);
    sem_post(&mutex_R);

    printf("  [R->L] Car %d entered bridge  (R on bridge: %d)\n", id, count_R);
}

void exit_bridge_right(int id) {
    sem_wait(&mutex_R);
    count_R--;
    printf("  [R->L] Car %d exited  bridge  (R remaining: %d)\n", id, count_R);
    if (count_R == 0)          /* last right car releases the bridge */
        sem_post(&bridge);
    sem_post(&mutex_R);
}

void *car_left(void *arg) {
    int id = *(int *)arg;
    printf("[L->R] Car %d approaching...\n", id);
    enter_bridge_left(id);
    usleep(300000);            /* simulate crossing time */
    exit_bridge_left(id);
    return NULL;
}

void *car_right(void *arg) {
    int id = *(int *)arg;
    printf("[R->L] Car %d approaching...\n", id);
    enter_bridge_right(id);
    usleep(300000);            /* simulate crossing time */
    exit_bridge_right(id);
    return NULL;
}

int main() {
    sem_init(&bridge,  0, 1);
    sem_init(&mutex_L, 0, 1);
    sem_init(&mutex_R, 0, 1);

    /* 4 left-going and 4 right-going cars, launched interleaved */
    int N = 4;
    pthread_t tL[N], tR[N];
    int idL[N], idR[N];

    printf("=== One Lane Bridge ===\n\n");

    for (int i = 0; i < N; i++) {
        idL[i] = i + 1;
        idR[i] = i + 1;
        pthread_create(&tL[i], NULL, car_left,  &idL[i]);
        usleep(50000);                          /* slight stagger */
        pthread_create(&tR[i], NULL, car_right, &idR[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(tL[i], NULL);
        pthread_join(tR[i], NULL);
    }

    sem_destroy(&bridge);
    sem_destroy(&mutex_L);
    sem_destroy(&mutex_R);

    printf("\nAll cars crossed safely.\n");
    return 0;
}
