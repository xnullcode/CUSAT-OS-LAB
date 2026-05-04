#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

// function for writing 

#define MAX_SIZE 5
int  buffer[MAX_SIZE], curr=0 , value =0;
pthread_mutex_t mutex;

void *writers(void *args){
    int i;
    for(i=0;i< MAX_SIZE;i++){
        pthread_mutex_lock(&mutex);
        
        buffer[curr]= value;
        printf("Writers entered %d at index %d \n",value,curr+1);
        value++;
        curr++;
        pthread_mutex_unlock(&mutex);
        usleep(600000);
    }
    return NULL;
}

void *reader(void *args){
    int i;
    usleep(500000);
    for(i=0;i<MAX_SIZE;i++){
        pthread_mutex_lock(&mutex);
        if(curr>0){
            curr--;
            printf("Reader read %d from index %d \n", buffer[curr], curr + 1);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL ;
}
int main(){
    pthread_t writer_thread,reader_thread;

    pthread_mutex_init(&mutex , NULL );
    pthread_create(&writer_thread, NULL , writers , NULL);
    pthread_create(&reader_thread, NULL , reader, NULL );

    pthread_join(writer_thread, NULL);
    pthread_join(reader_thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
// lock , write , unlock
