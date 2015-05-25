#include <stdio.h>

int main(void)
{
	int c;

	//mrs 读cpsr
	//msr 写cpsr

	asm volatile(
		"mrs %0, cpsr\n"//%0=cpsr
		:"=&r"(c)
	);

	printf("c = %x\n", c);

	//N=0Z=0C=0=0Q
	asm volatile(
		"mov r0, #3\n"
		"adds r0, r0, #0\n"
		:::"r0"
	);

	asm volatile(
		"mrs %0, cpsr\n"//%0=cpsr
		:"=&r"(c)
	);

	printf("c = %x\n", c);

	asm volatile(
		"mrs r0, cpsr\n"
		"mvn r1, #0\n"
		"orr r0, r0, r1\n"
		"msr cpsr, r0\n"//cpsr=r0
		:::"r0", "r1"
	);

	asm volatile(
		"msr cpsr, #0xff\n"
	);

	asm volatile(
		"mrs %0, cpsr\n"//%0=cpsr
		:"=&r"(c)
	);

	printf("c = %x\n", c);

	return 0;
}



