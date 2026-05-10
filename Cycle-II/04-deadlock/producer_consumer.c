#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define MAX_SIZE 5

pthread_mutex_t mutex;
pthread_cond_t not_full , not_empty ;

int in = 0, out = 0 ,count=0, buffer[10];

void *producer(void *args){
    int i, value =0;
    for(i=0;i<10;i++){
        pthread_mutex_lock(&mutex);

        while(count == MAX_SIZE){
            pthread_cond_wait(&not_full, &mutex);
        }
        buffer[in]= value;
        printf("Produced %d to %d\n",value,in);
        value ++;
        count ++;
        in = (in+1) % MAX_SIZE;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        usleep(500000);
    }
    return NULL;
}

void *consumer(void *args){
    int i = 0 ;
    int item = 0 ;
    for(i=0;i<10;i++){
        pthread_mutex_lock(&mutex);
        while(count==0){
            pthread_cond_wait(&not_empty, &mutex);
        }
        item = buffer[out];
        printf("consumed %d from %d\n", item , out);
        out = (out + 1 ) % MAX_SIZE;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        usleep(700000);

    }
    return NULL ;
}

int main(){
    pthread_t consumer_thread, producer_thread;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty,NULL);

    pthread_create(&consumer_thread,NULL , consumer, NULL);
    pthread_create(&producer_thread,NULL , producer, NULL);

    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
