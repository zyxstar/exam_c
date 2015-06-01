#include <common.h>
#include <hardware.h>
#include <led.h>
#include <chip_id.h>
#include <clock.h>
#include <button.h>
#include <uart.h>

int main(void)
{
	char c;
	char buf[32];

	uart_init(0);

	c = ugetchar();		

	uputchar(c);

	ugets(buf, 32);
	uputs(buf);

	printf("nihao\n");
	//printf("%d %c %x %s\n", 100, 'a', 0x400, "nihao");

	return 0;
}




