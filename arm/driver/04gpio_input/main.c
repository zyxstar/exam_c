#include <common.h>
#include <hardware.h>
#include <led.h>
#include <chip_id.h>
#include <button.h>

int main(void)
{
	int ret;

	button_init();

	while(1){
		ret = button_state();	
		if(ret != 4)
			printf("button %d is down\n", ret);
	}

	return 0;
}
