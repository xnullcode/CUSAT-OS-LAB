#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in = 0;
int out = 0;

/* Semaphores */
sem_t mutex;
sem_t empty;
sem_t full;

/* Producer Function */
void *producer(void *arg)
{
    int item;
    for(int i = 1; i <= 5; i++)
    {
        item = i;
        
        /* Check for empty space */
        sem_wait(&empty);
        
        /* Enter critical section */
        sem_wait(&mutex);

        buffer[in] = item;

        printf("Produced : %d at %d\n", item, in);

        in = (in + 1) % SIZE;

        /* Exit critical section */
        sem_post(&mutex);

        /* Increase full count */
        sem_post(&full);
    }

    return NULL;
}

/* Consumer Function */
void *consumer(void *arg)
{
    int item;

    for(int i = 1; i <= 5; i++)
    {
        /* Check for filled slots */
        sem_wait(&full);

        /* Enter critical section */
        sem_wait(&mutex);

        item = buffer[out];

        printf("Consumed : %d from %d\n", item, out);

        out = (out + 1) % SIZE;

        /* Exit critical section */
        sem_post(&mutex);

        /* Increase empty count */
        sem_post(&empty);
    }

    return NULL;
}

int main()
{
    pthread_t p1, c1;

    /* Initialize Semaphores */
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    /* Create Threads */
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, NULL);

    /* Wait for Threads */
    pthread_join(p1, NULL);
    pthread_join(c1, NULL);

    /* Destroy Semaphores */
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
