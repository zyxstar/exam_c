#ifndef __CHIP_ID_H__
#define __CHIP_ID_H__

extern int read_chip(void);

#define PRO_ID (*(volatile unsigned int *)0x10000000)

#endif
