#include <stdio.h>

int main(void)
{
	int in = 5;
	int out = 6;
	int a;
	int in_out = 100;

	//out = in_out
	//in_out = in;

	asm volatile(
		"mov "
		"%[a], %[b]\n"
		//"mov %0, %1\n"
		"mov %[b], %[c]"
		:[a]"=&r"(out), [b]"+r"(in_out), "=&r"(a)
		:[c]"r"(in)
		:
	);

	printf("out = %d\n", out);
	printf("in_out = %d\n", in_out);

	return 0;
}
