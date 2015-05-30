#include <common.h>
#include <hardware.h>
#include <chip_id.h>

int main(void)
{
	hardware_init();
	hardware_ops();
		
	printf("%x\n", read_chip());

	return 0;
}
