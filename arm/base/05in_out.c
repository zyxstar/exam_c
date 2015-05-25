#include <stdio.h>

int main(void)
{
	int in = 5;
	int out = 6;
	int in_out = 100;

	//out = in_out
	//in_out = in;

	asm volatile(
		"mov "
		"%0, %1\n"
		//"mov %0, %1\n"
		"mov %1, %2"
		:"=&r"(out), "+r"(in_out)
		:"r"(in)
		:
	);

	printf("out = %d\n", out);
	printf("in_out = %d\n", in_out);

	return 0;
}
