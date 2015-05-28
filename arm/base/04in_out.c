#include <stdio.h>

int main(void)
{
	int in = 40;
	int out = 23;

	//out = in;

	asm volatile(
		"mov %0, %1"//%0=%1
		:"=&r"(out)
		:"r"(in)//输入变量
		:
	);

	printf("out = %d\n", out);

	return 0;
}
