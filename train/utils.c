#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

void debug_write(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[1024];
    sprintf(new_format, LIGHT_BLUE "DEBUG: %s" COLOR_NONE, format);
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
