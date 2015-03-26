#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NAMESIZE 32

struct AgentInfo{
    int agent_id;
    int *num_tickets_p;
};


sem_t sem_s;
sem_t sem_m;


void *sell_tickets(void *arg){
    struct AgentInfo *st_info = arg;
    while(1){
        sem_wait(&sem_s);
        if(*st_info->num_tickets_p == 0){
            break;
        }
        printf("Agent %d sells a ticket %d\n", st_info->agent_id, *st_info->num_tickets_p);
        sem_post(&sem_m);    
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
    sem_init(&sem_s, 0, 0);
    sem_init(&sem_m, 0, 0);


    for(i = 0; i < numAgents; i++){
        st_info = malloc(sizeof(struct AgentInfo));
        st_info->agent_id = i;
        st_info->num_tickets_p = &numTickets;
        pthread_create(tid + i, NULL, sell_tickets, (void *)st_info);
    }

    while(1){
        if(numTickets == 0)
            break;
        sem_post(&sem_s);
        numTickets--;
        sem_wait(&sem_m);
        // if((rand() % 100) > 90)
        //     sleep(1);
    }

    for(i = 0; i < numAgents; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&sem_s);
    sem_destroy(&sem_m);

    return 0;
}
