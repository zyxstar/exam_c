#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFSIZE 8

static char buffer[BUFSIZE];
static sem_t empty_buffers;
static sem_t full_buffers;

static void *writer(void *unuse){
    int i;
    for(i=0; i<40; i++){
        char c = rand()%26 + 'A';
        sem_wait(&empty_buffers);
        buffer[i%BUFSIZE] = c;
        sem_post(&full_buffers);
    }
    return NULL;
}

static void *reader(void *unuse){
    int i;
    for(i=0; i<40; i++){
        sem_wait(&full_buffers);
        char c = buffer[i%BUFSIZE];
        sem_post(&empty_buffers);
        putchar(c);
    }
    return NULL;
}


int main(){
    pthread_t tid[2];

    srand(time(NULL));
    sem_init(&empty_buffers, 0, BUFSIZE);
    sem_init(&full_buffers, 0, 0);

    pthread_create(tid, NULL, writer, NULL);
    pthread_create(tid + 1, NULL, reader, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sem_destroy(&empty_buffers);
    sem_destroy(&full_buffers);

    printf("\n");
    return 0;
}
