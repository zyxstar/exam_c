#include <stdio.h>

int main(void)
{
	int a, b, c;
	
//fd fa ed ea 

	asm volatile(
		//"ldr %0, [sp]\n"
		//"mov r0, #10\n"
		//"str r0, [sp]\n"
		
		"mov r0, #1\n"
		"mov r1, #2\n"
		"mov r2, #3\n"
		//"push {r0-r2}\n"
		//"pop {r3-r4, r5}\n"
		"stmfd sp!, {r0-r2}\n"
		"ldmfd sp!, {r3-r4, r5}\n"
		"mov %0, r3\n"
		"mov %1, r4\n"
		"mov %2, r5\n"
		:"=&r"(a), "=&r"(b), "=&r"(c)
		:
		:"r0", "r1", "r2", "r3", "r4", "r5"
	);

	printf("a = %x\n", a);
	printf("b = %x\n", b);
	printf("c = %x\n", c);

	return 0;
}
