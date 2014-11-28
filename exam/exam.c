#include <unistd.h>
#include <signal.h>
#include <stdio.h>

typedef void(*CALL_FN)(int);

typedef struct{
    int interval;
    CALL_FN call_fn;
} TIMER;

TIMER *g_timer;
void _handler(int i){
    g_timer->call_fn(i);
    alarm(g_timer->interval);    
}

CALL_FN _wrap(TIMER *timer){
    g_timer = timer;
    return _handler;
}



void timer_new(TIMER *timer, int interval, CALL_FN call_fn){
    timer->interval = interval;
    timer->call_fn = call_fn;
    signal(SIGALRM, _wrap(timer));
}

void timer_start(TIMER *timer){
    alarm(timer->interval);
}






void handler(int i){
    printf("Hello %d %d\n", i, SIGALRM);
}





void main()
{

    TIMER t;
    timer_new(&t, 2, handler);
    timer_start(&t);

    // printf("%p %p %p\n", &(t.interval), &(t.call_fn), t.call_fn);
    // t.call_fn = handler;
    // printf("%p\n", handler);
    // printf("%p %p %p\n", &(t.interval), &(t.call_fn), t.call_fn);


    int i;
    //timer();
    for(i=1;i<21;i++)
    {
        printf("sleep %d ...\n",i);
        sleep(1);
    }
}
