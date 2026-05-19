#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/* Shared variables */
int data = 1;
int read_count = 0;

/* Semaphores */
sem_t mutex; // Controls access to read_count
sem_t wrt;   // Controls access to the shared data

/* Writer Function */
void *writer(void *arg)
{
    int w_id = *((int *)arg);

    /* Wait for exclusive access to shared data */
    sem_wait(&wrt);

    /* Critical Section: Writing */
    data = data * 2;
    printf("Writer %d modified data to %d\n", w_id, data);

    /* Release exclusive access */
    sem_post(&wrt);

    return NULL;
}

/* Reader Function */
void *reader(void *arg)
{
    int r_id = *((int *)arg);

    /* Entry section: Safely update read_count */
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
    {
        /* First reader locks the resource from writers */
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    /* Critical Section: Reading (multiple readers can be here) */
    printf("Reader %d reads data as %d\n", r_id, data);

    /* Exit section: Safely update read_count */
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
    {
        /* Last reader releases the resource for writers */
        sem_post(&wrt);
    }
    sem_post(&mutex);

    return NULL;
}

int main()
{
    pthread_t r[5], w[5];
    int ids[5] = {1, 2, 3, 4, 5};

    /* Initialize Semaphores */
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    /* Create Threads */
    for (int i = 0; i < 3; i++) {
        pthread_create(&w[i], NULL, writer, &ids[i]);
        pthread_create(&r[i], NULL, reader, &ids[i]);
    }
    for (int i = 3; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &ids[i]);
    }

    /* Wait for Threads to complete */
    for (int i = 0; i < 3; i++) {
        pthread_join(w[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }

    /* Destroy Semaphores */
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
