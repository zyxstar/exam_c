#include <stdio.h>
#include <stdlib.h>
#include "event.h"



static void _e_handler1(void *sender, void *receiver, void *arg){
    int *sender2 = sender;
    int *receiver2 = receiver;
    int *arg2 = arg;
    printf("_e_handler1 %d %d %d\n", *sender2, *receiver2, *arg2);
}

static void _e_handler2(void *sender, void *receiver, void *arg){
    int *sender2 = sender;
    int *receiver2 = receiver;
    int *arg2 = arg;
    printf("_e_handler2 %d %d %d\n", *sender2, *receiver2, *arg2);
}

void test_event(){
    int sender = 10;
    EVENT *e = event_new(&sender);
    int receiver = 100;
    event_add(e, &receiver, _e_handler1);
    event_add(e, &receiver, _e_handler2);

    int arg = 20;
    event_trigger(e, &arg);

    event_remove(e, &receiver, _e_handler1);
    arg = 30;
    event_trigger(e, &arg);

    event_free(e);
}


int main(){

    test_event();

    return 0;
}


// gcc -I ../ ../event.c test_event.c -o test_event.out && ./test_event.out
