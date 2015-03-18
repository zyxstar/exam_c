#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo){
    printf("alarm\n");
}

int main(){
    struct sigaction act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGALRM);
    act.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &act, NULL);

    alarm(3);

    while(1){
        pause();
        printf("after pause\n");
    }

    return 0;
}
