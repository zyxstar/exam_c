#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define PH_COUNT 5

static sem_t forks[PH_COUNT];
static sem_t num_allowed_to_eat;

static void *philosopher(void *arg){
    int id = (int)arg;
    int i;
    printf("id %d begin!\n", id);
    for(i=0; i<10; i++){

        if((rand() % 100) > 90)
            sleep(1);
        printf("%d think\n", id);

        sem_wait(&num_allowed_to_eat);

        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % PH_COUNT]);

        if((rand() % 100) > 90)
            sleep(1);
        printf("%d eat\n", id);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % PH_COUNT]);

        sem_post(&num_allowed_to_eat);
    }
    printf("id %d done!\n", id);
    return NULL;
}

int main(){
    pthread_t tid[PH_COUNT];
    int i;
    srand(time(NULL));

    sem_init(&num_allowed_to_eat, 0, PH_COUNT - 1);
    for(i = 0; i< PH_COUNT; i++)
        sem_init(forks + i, 0, 1);

    for(i = 0; i< PH_COUNT; i++)
        pthread_create(tid + i, NULL, philosopher, (void *)i);

    for(i = 0; i< PH_COUNT; i++)
        pthread_join(tid[i], NULL);

    for(i = 0; i< PH_COUNT; i++)
        sem_destroy(forks + i);

    sem_destroy(&num_allowed_to_eat);

    return 0;
}
