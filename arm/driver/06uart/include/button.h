#ifndef __BUTTON_H__
#define __BUTTON_H__

extern void button_init(void);
extern int button_state(void);

#define GPX3CON (*(volatile unsigned int *)(0x11000000 + 0x0C60))
#define GPX3DAT (*(volatile unsigned int *)(0x11000000 + 0x0C64))

#endif
