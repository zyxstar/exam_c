#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"

void debug_write(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, LIGHT_BLUE "#DEBUG# %s" COLOR_NONE, format);
    vfprintf(stderr, new_format, ap);
    va_end(ap);
}

void printf_correct(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, GREEN "%s" COLOR_NONE, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_error(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, RED "%s" COLOR_NONE, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_info(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, BROWN "%s" COLOR_NONE, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}


const char* human_bool(BOOL val){
    if(val) return "TRUE";
    return "FALSE";
}




static void _timer_wrap_callee_fn(){
    DEBUG_WRITE(("timer_call begin: [callee_name]%s [interval]%d\n", GLOBAL_SIMPLE_TIMER.callee_name, GLOBAL_SIMPLE_TIMER.interval));
    GLOBAL_SIMPLE_TIMER.callee_fn();
    DEBUG_WRITE(("timer_call end: [callee_name]%s [interval]%d\n", GLOBAL_SIMPLE_TIMER.callee_name, GLOBAL_SIMPLE_TIMER.interval));

    alarm(GLOBAL_SIMPLE_TIMER.interval);
}

void _timer_set_callee_name(char *source){
    strcpy(GLOBAL_SIMPLE_TIMER.callee_name, source);
}

void _timer_set(int interval, void(*callee_fn)()){
    GLOBAL_SIMPLE_TIMER.interval = 0;
    GLOBAL_SIMPLE_TIMER.const_interval = interval;
    GLOBAL_SIMPLE_TIMER.callee_fn = callee_fn;
    signal(SIGALRM, _timer_wrap_callee_fn);
    DEBUG_WRITE(("timer_new: [callee_name]%s [interval]%d\n", GLOBAL_SIMPLE_TIMER.callee_name, GLOBAL_SIMPLE_TIMER.const_interval));
}

void timer_start(){
    GLOBAL_SIMPLE_TIMER.interval = GLOBAL_SIMPLE_TIMER.const_interval;
    alarm(GLOBAL_SIMPLE_TIMER.interval);
    DEBUG_WRITE(("timer_start: [callee_name]%s [interval]0 -> %d\n", GLOBAL_SIMPLE_TIMER.callee_name, GLOBAL_SIMPLE_TIMER.interval));
}

void timer_stop(){
    DEBUG_WRITE(("timer_stop: [callee_name]%s [interval]%d -> 0\n", GLOBAL_SIMPLE_TIMER.callee_name, GLOBAL_SIMPLE_TIMER.interval));
    GLOBAL_SIMPLE_TIMER.interval = 0;
}
