#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include "console.h"

#define FORMAT_LEN (1024)

void debug_write(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[FORMAT_LEN];
    snprintf(new_format, FORMAT_LEN, VT_RESET VT_PURPLE "#DEBUG# %s" VT_RESET, format);
    vfprintf(stderr, new_format, ap);
    va_end(ap);
}

void printf_correct(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[FORMAT_LEN];
    snprintf(new_format, FORMAT_LEN, VT_RESET VT_GREEN "%s" VT_RESET, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_error(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[FORMAT_LEN];
    snprintf(new_format, FORMAT_LEN, VT_RESET VT_RED "%s" VT_RESET, format);
    vfprintf(stdout, new_format, ap);
    va_end(ap);
}

void printf_info(char *format, ...){
    va_list ap;
    va_start(ap, format);
    char new_format[FORMAT_LEN];
    snprintf(new_format, FORMAT_LEN, VT_RESET VT_YELLOW "%s" VT_RESET, format);
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



