#ifndef __COMMON_H__
#define __COMMON_H__

#define udelay(us) (((void (*)(int))0x43e25e88)(us))

#define printf(...)     (((int (*)(const char *, ...))0x43e11434)(__VA_ARGS__))
#define NULL (void *)0

#endif
