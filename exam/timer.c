#include <stdio.h>
#include "utils.h"


void handler(){
    printf("hello\n");
}


void handler2(){
    printf("world\n");
}



int main(){
    // printf("%s\n", __FILE__);
    // printf("%d\n", __LINE__);
    // printf("%s\n", __FUNCTION__);
    // printf("%s\n", __func__);

    timer_new(3, handler);
    timer_start();
    // printf("%d\n", timer_interval());

    int i;
    for(i = 1;i<100; i++){
        printf("%d %s\n", i, timer_callee_name());
        sleep(1);
        if(i == 5) {
            timer_new(3, handler2);
            timer_start();

        }
        if(i == 10) timer_stop();

    }

    return 0;
}







// gcc -I ../utils ../utils/utils.c timer.c -DDEBUG -o timer.out && ./timer.out
