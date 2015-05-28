#include <stdio.h>

int main(void)
{
#if 0
	int a;

	asm volatile(
		"mov r0, #5\n"		
		"mov r1, #2\n"
		//"sub r2, r0, r1\n"//r2=r0-r1
		//"sub r0, r0, r1\n"//r0-=r1
		//"sub r0, r1\n"//r0-=r1
		"sub %0, r0, r1\n"
		:"=&r"(a)
		:
		:"r0", "r1"
	);

	printf("a = %d\n", a);
#endif
	int a, b;
	
	//0x0000000900000004
	//0x0000000400000005
	//0x00000004ffffffff

	//asm volatile(
	__asm__ __volatile__(
		"mov r0, #4\n"
		"mov r1, #5\n"
		"subs %0, r0, r1\n"//clear C
		"mov r0, #9\n"
		"mov r1, #4\n"
		"sbc %1, r0, r1\n"//%1=r0-r1-!C
		:"=&r"(a), "=&r"(b)
		:
		:"r0", "r1"
	);

	printf("%#010x%08x\n", b, a);

	return 0;
}





