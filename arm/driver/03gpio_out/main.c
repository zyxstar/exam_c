#include <common.h>
#include <hardware.h>
#include <led.h>
#include <chip_id.h>

int main(void)
{
	int count = 100;

	hardware_init();
	hardware_ops();
		
	printf("%x\n", read_chip());

	led_init();

	while(count--){
		led_on(count % 4);
		udelay(500000);
		led_off(count % 4);
		udelay(500000);
	}

	return 0;
}
