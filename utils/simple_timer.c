#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include "simple_timer.h"
#include "console.h"


static struct{
    BOOL is_start;
    int size;
    SIMPER_TIMER *timer_queue[64];
} GLOBAL_TIMER_QUEUE;

void _timer_set_callee_name(SIMPER_TIMER *timer, char *file, int line, char *name){
    snprintf(timer->callee_name, 256, "%s:%d:%s", file, line, name);
}

void _timer_new(SIMPER_TIMER *timer, int interval, void(*callee_fn)(void *env), void *env){

    timer->interval = 0;
    timer->const_interval = interval;
    timer->count = 0;
    timer->callee_fn = callee_fn;
    timer->env = env;

    int i;
    for(i = 0; i < GLOBAL_TIMER_QUEUE.size; i++){
        if(GLOBAL_TIMER_QUEUE.timer_queue[i] == NULL){
            GLOBAL_TIMER_QUEUE.timer_queue[i] = timer;
            break;
        }
    }
    if(i == GLOBAL_TIMER_QUEUE.size){
        if(GLOBAL_TIMER_QUEUE.size == 64) return;
        GLOBAL_TIMER_QUEUE.timer_queue[GLOBAL_TIMER_QUEUE.size] = timer;
        GLOBAL_TIMER_QUEUE.size++;
    }
    DEBUG_WRITE(("timer_new: [callee_name]%s [interval]%d\n", timer->callee_name, timer->interval));
}

static void _timer_wrap_callee_fn(){
    int i;
    SIMPER_TIMER *timer;
    for(i = 0; i < GLOBAL_TIMER_QUEUE.size; i++){
        timer = GLOBAL_TIMER_QUEUE.timer_queue[i];
        if(timer == NULL || timer->interval == 0) continue;
        timer->count++;
        if(timer->count % (timer->interval / 10) == 0 && timer->count / (timer->interval / 10) > 0){
            DEBUG_WRITE(("timer_call begin: [callee_name]%s [interval]%d\n", timer->callee_name, timer->interval));
            timer->callee_fn(timer->env);
            DEBUG_WRITE(("timer_call end: [callee_name]%s [interval]%d\n", timer->callee_name, timer->interval));
        }
    }
    signal(SIGALRM, _timer_wrap_callee_fn);
}

void timer_start(SIMPER_TIMER *timer){
    if(!GLOBAL_TIMER_QUEUE.is_start){
        signal(SIGALRM, _timer_wrap_callee_fn);
        struct itimerval tv, otv;
        tv.it_value.tv_sec = 0;
        tv.it_value.tv_usec = 10000;
        //after the first time, how long to run next time
        tv.it_interval.tv_sec = 0;
        tv.it_interval.tv_usec = 10000;  //0.01 seconds == 10 milliseconds
        setitimer(ITIMER_REAL, &tv, &otv);

        GLOBAL_TIMER_QUEUE.is_start = TRUE;
    }
    timer->interval = timer->const_interval;
    DEBUG_WRITE(("timer_start: [callee_name]%s [interval]0 -> %d\n", timer->callee_name, timer->interval));
}

void timer_stop(SIMPER_TIMER *timer){
    DEBUG_WRITE(("timer_stop: [callee_name]%s [interval]%d -> 0\n", timer->callee_name, timer->interval));
    timer->interval = 0;
    timer->count = 0;
}

void timer_destroy(SIMPER_TIMER *timer){
    if(timer == NULL) return;
    timer_stop(timer);
    int i;
    for(i = 0; i < GLOBAL_TIMER_QUEUE.size; i++){
        if(timer == GLOBAL_TIMER_QUEUE.timer_queue[i]){
            DEBUG_WRITE(("timer_destroy: [callee_name]%s [interval]%d\n", timer->callee_name, timer->interval));
            GLOBAL_TIMER_QUEUE.timer_queue[i] = NULL;
            return;
        }
    }
}

void timer_set_interval(SIMPER_TIMER *timer, int interval){
    DEBUG_WRITE(("timer_set_interval: [callee_name]%s [interval]%d -> %d\n", timer->callee_name, timer->const_interval, interval));
    timer->const_interval = interval;
    timer->interval = interval;
    timer->count = 0;

}
