#include <stdio.h>
#include "utils.h"


void handler(void *env){
    printf("hello %d\n", *((int*)env));
}


void handler2(void *env){
    printf("world %d\n", *((int*)env));
}



int main(){
    int data = 999;
    void *env = &data;
    timer_new(3, handler, env);
    timer_start();
    // printf("%d\n", timer_interval());

    int i;
    for(i = 1;i<100; i++){
        printf("%d %s\n", i, timer_callee_name());
        sleep(1);
        if(i == 5) {
            timer_new(3, handler2, env);
            timer_start();

        }
        if(i == 10) timer_stop();

    }

    return 0;
}







// gcc -I ../utils ../utils/utils.c timer.c -DDEBUG -o timer.out && ./timer.out
