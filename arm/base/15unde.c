#include <stdio.h>

int main(void)
{
	//内嵌的指令是处在代码段
	asm volatile(
		".word 0x77777777\n"
	);

	return 0;
}
