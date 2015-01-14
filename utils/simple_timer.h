#ifndef SIMPER_TIMER_H_INCLUEDE
#define SIMPER_TIMER_H_INCLUEDE


typedef struct{
    int interval; //millisecond
    int const_interval;
    int count;
    char callee_name[256];
    void(*callee_fn)(void *env);
    void *env;
} SIMPER_TIMER;





void _timer_new(SIMPER_TIMER *timer, int interval, void(*callee_fn)(void *env), void *env);

void _timer_set_callee_name(SIMPER_TIMER *timer, char *file, int line, char *name);

void timer_start(SIMPER_TIMER *timer);
void timer_stop(SIMPER_TIMER *timer);
void timer_destroy(SIMPER_TIMER *timer);
void timer_set_interval(SIMPER_TIMER *timer, int interval);

#define timer_new(arg1, arg2, arg3, arg4) \
        _timer_set_callee_name(arg1, __FILE__, __LINE__, #arg3);\
        _timer_new((arg1), (arg2), (arg3), (arg4))



#endif
