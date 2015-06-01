#ifndef __LED_H__
#define __LED_H__

extern void led_init(void);
extern void led_on(int no);
extern void led_off(int no);

#define GPM4CON (*(volatile unsigned int *)(0x11000000 + 0x2e0))
#define GPM4DAT (*(volatile unsigned int *)(0x11000000 + 0x2e4))

#endif


