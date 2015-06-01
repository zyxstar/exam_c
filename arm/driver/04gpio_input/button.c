#include <button.h>
#include <common.h>

void button_init(void)
{
	GPX3CON &= ~(0xffff << 8);
}

int button_state(void)
{
	int ret;

	switch((GPX3DAT >> 2) & 0xf){
		case 0xe:
			ret = 0;
			break;
		case 0xd:
			ret = 1;
			break;
		case 0xb:
			ret = 2;
			break;
		case 0x7:
			ret = 3;
			break;
		case 0xf:
		default:
			ret = 4; 
	}

	return ret;
}




