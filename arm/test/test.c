#include <stdio.h>

int main(void)
{
	int a, b;

	asm volatile(
		"mov %0, #-1\n"		
		"mvn %1, #0\n"
		:"=&r"(a), "=&r"(b)
		:
		:"r0", "r1"
	);

	printf("%d %d\n", a, b);
	printf("%x %x\n", a, b);
}




