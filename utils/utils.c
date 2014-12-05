#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include "utils.h"

void debug_write(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, VT_RESET "\033[35m#DEBUG# %s" VT_RESET, format);
    vfprintf(stderr, new_format, ap);
    va_end(ap);
}

void printf_correct(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, VT_RESET VT_GREEN "%s" VT_RESET, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_error(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, VT_RESET VT_RED "%s" VT_RESET, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_info(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, VT_RESET VT_YELLOW "%s" VT_RESET, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}


const char* human_bool(BOOL val){
    if(val) return "TRUE";
    return "FALSE";
}


static struct termios stored_settings1;
static struct termios stored_settings2;

void echo_off(){
    struct termios new_settings;
    tcgetattr(0,&stored_settings1);
    new_settings =stored_settings1;
    new_settings.c_lflag &= (~ECHO);
    tcsetattr(0,TCSANOW,&new_settings);
}

void echo_on(){
    tcsetattr(0,TCSANOW,&stored_settings1);
}

void set_keypress(){
    struct termios new_settings;
    tcgetattr(0,&stored_settings2);
    new_settings = stored_settings2;

    /*Disable canornical mode, and set buffer size to 1 byte */
    new_settings.c_lflag&=(~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0, TCSANOW, &new_settings);
}

void reset_keypress(){
    tcsetattr(0, TCSANOW, &stored_settings2);
}




void _timer_set_callee_name(SIMPER_TIMER *timer, char *file, int line, char *name){
    sprintf(timer->callee_name, "%s:%d:%s", file, line, name);
}

void _timer_new(SIMPER_TIMER *timer, int interval, void(*callee_fn)(void *env), void *env){
    if(GLOBAL_TIMER_QUEUE.size == 64) return;
    timer->interval = 0;
    timer->const_interval = interval;
    timer->count = 0;
    timer->callee_fn = callee_fn;
    timer->env = env;
    GLOBAL_TIMER_QUEUE.timer_queue[GLOBAL_TIMER_QUEUE.size] = timer;
    GLOBAL_TIMER_QUEUE.size++;
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
    timer->const_interval = interval;
    timer->interval = interval;
    timer->count = 0;
}


