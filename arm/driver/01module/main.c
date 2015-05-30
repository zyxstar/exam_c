#include <common.h>
#include <hardware.h>

int main(void)
{
	hardware_init();
	hardware_ops();

	return 0;
}
