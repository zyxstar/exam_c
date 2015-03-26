#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// #include <semaphore.h>

#define NAMESIZE 32

struct AgentInfo{
    int agent_id;
    int *num_tickets_p;
};


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void *sell_tickets(void *arg){
    struct AgentInfo *st_info = arg;
    while(1){
        pthread_mutex_lock(&mutex);
        if(*st_info->num_tickets_p == 0){
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Agent %d sells a ticket %d\n", st_info->agent_id, *st_info->num_tickets_p);
        (*st_info->num_tickets_p)--;
        pthread_mutex_unlock(&mutex);

        if((rand() % 100) > 50)
            sleep(1);
    }
    printf("Agent %d done!\n", st_info->agent_id);
    free(st_info);
    return NULL;
}



int main(){
    int numAgents = 10;
    int numTickets = 150;
    int i;
    struct AgentInfo *st_info;

    pthread_t tid[numAgents];

    srand(time(NULL));
    for(i = 0; i < numAgents; i++){
        st_info = malloc(sizeof(struct AgentInfo));
        st_info->agent_id = i;
        st_info->num_tickets_p = &numTickets;
        pthread_create(tid + i, NULL, sell_tickets, (void *)st_info);
    }

    for(i = 0; i < numAgents; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
