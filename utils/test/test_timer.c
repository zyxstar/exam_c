#include <stdio.h>
#include "simple_timer.h"


void tick(void *env){
    int *data = env;
    fprintf(stderr, "%d\n", *data);
}

int main(){
    SIMPER_TIMER t;
    int data = 1;
    timer_new(&t, 1000, tick, &data);

    fprintf(stderr, "start\n");
    timer_start(&t);
    int i;

    getchar();
    fprintf(stderr, "set\n");
    data = 2;
    timer_set_interval(&t, 2000);

    getchar();
    fprintf(stderr, "stop\n");
    timer_stop(&t);

    getchar();
    fprintf(stderr, "start\n");
    timer_start(&t);

    getchar();
    fprintf(stderr, "destroy\n");
    timer_destroy(&t);

    getchar();
}

// gcc -DDEBUG -I../ ../simple_timer.c ../console.c test_timer.c -o test_timer.out && ./test_timer.out
