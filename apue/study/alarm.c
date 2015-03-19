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
    //sigaction(SIGALRM, &act, NULL);

    int a = alarm(30);
    int b = alarm(20);
    int c = alarm(40);
    printf("%d %d %d %d\n", a, b, c, alarm(0));

    // while(1){
        pause();
    //     printf("after pause\n");
    // }

    return 0;
}
