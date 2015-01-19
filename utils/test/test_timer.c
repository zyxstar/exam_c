#include <stdio.h>
#include <simple_timer.h>
// #include <signal.h>
// #include <unistd.h>
// #include <sys/time.h>

void tick(void *env){
    int *data = env;
    fprintf(stderr, "%d\n", *data);
    int i;
    for(i = 0; i < 5; i++) {
        printf("i = %d\n", i);
        sleep(1);
    }
}

int main(){
    int c;
    SIMPER_TIMER t;
    int data = 1;
    timer_new(&t, 1000, tick, &data);

    fprintf(stderr, "start\n");
    timer_start(&t);

    while( (c = getchar()) == -1);

    fprintf(stderr, "set\n");
    data = 2;
    timer_set_interval(&t, 2000);

    while( (c = getchar()) == -1);
    fprintf(stderr, "stop\n");
    timer_stop(&t);

    while( (c = getchar()) == -1);
    fprintf(stderr, "start\n");
    timer_start(&t);

    while( (c = getchar()) == -1);
    fprintf(stderr, "destroy\n");
    timer_destroy(&t);

    while( (c = getchar()) == -1);
}

// gcc -DDEBUG -I../ ../simple_timer.c ../console.c test_timer.c -o test_timer.out && ./test_timer.out

