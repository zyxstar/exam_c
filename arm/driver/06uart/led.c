#include <common.h>
#include <led.h>

void led_init(void)
{
	GPM4CON &= ~0xffff;
	GPM4CON |= 0x1111;

	GPM4DAT |= 0xf;	
}

void led_on(int no)
{
	if(no > 3 || no < 0)
		return;
	GPM4DAT &= ~(1 << no);
}

void led_off(int no)
{
	if(no > 3 || no < 0)
		return;
	GPM4DAT |= (1 << no);
}





