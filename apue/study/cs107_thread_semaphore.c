#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NAMESIZE 32

struct AgentInfo{
    int agent_id;
    int *num_tickets_p;
};


static sem_t sem;

static void *sell_tickets(void *arg){
    struct AgentInfo *st_info = arg;
    while(1){
        sem_wait(&sem);
        if(*st_info->num_tickets_p == 0){
            sem_post(&sem);
            break;
        }
        printf("Agent %d sells a ticket %d\n", st_info->agent_id, *st_info->num_tickets_p);
        (*st_info->num_tickets_p)--;
        sem_post(&sem);

        if((rand() % 100) > 90)
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
    sem_init(&sem, 0, 1);

    for(i = 0; i < numAgents; i++){
        st_info = malloc(sizeof(struct AgentInfo));
        st_info->agent_id = i;
        st_info->num_tickets_p = &numTickets;
        pthread_create(tid + i, NULL, sell_tickets, (void *)st_info);
    }

    for(i = 0; i < numAgents; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&sem);

    return 0;
}
