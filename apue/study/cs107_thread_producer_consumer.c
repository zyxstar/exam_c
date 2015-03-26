#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NAMESIZE 32


char buffer[8];
Semaphore emptyBuffers = SemaphoreNew(-,8);
Semaphore fullBuffers = SemaphoreNew(-,0);
 
void Writer(){
    for(int i=0; i<40; i++){
        char c = PrepareRandomChar();
        SemaphoreWait(emptyBuffers);
        buffer[i%8] = c;
        SemaphoreSignal(fullBuffers);
    }
}
 
void Reader(){
    for(int i=0; i<40; i++){
        SemaphoreWait(fullBuffers);
        char c = buffer[i%8];
        SemaphoreSignal(emptyBuffers);
        ProcessChar(c);
    }
}
 
int main(){
    InitThreadPackage(false);
    ThreadNew("Writer", Writer, 0);
    ThreadNew("Reader", Reader, 0);
    RunAllThreads();
　　return 0;
}


struct AgentInfo{
    int agent_id;
    int *num_tickets_p;
};


sem_t bin_sem;

void *sell_tickets(void *arg){
    struct AgentInfo *st_info = arg;
    while(1){
        sem_wait(&bin_sem);
        if(*st_info->num_tickets_p == 0){
            sem_post(&bin_sem);
            break;
        }
        printf("Agent %d sells a ticket %d\n", st_info->agent_id, *st_info->num_tickets_p);
        (*st_info->num_tickets_p)--;
        sem_post(&bin_sem);

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
    sem_init(&bin_sem, 0, 0);

    for(i = 0; i < numAgents; i++){
        st_info = malloc(sizeof(struct AgentInfo));
        st_info->agent_id = i;
        st_info->num_tickets_p = &numTickets;
        pthread_create(tid + i, NULL, sell_tickets, (void *)st_info);
    }
    sem_post(&bin_sem);


    for(i = 0; i < numAgents; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
