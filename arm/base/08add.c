#include <stdio.h>

int main(void)
{
#if 0
	int a;

	asm volatile(
		"mov r0, #4\n"
		"mov r1, #5\n"
		//"add r2, r0, r1\n"//r2=r0+r1
		//"add r0, r1\n"//r0+=r1
		//"add r0, r0, r1\n"//r0=r0+r1
		"add %0, r0, r1\n"//r0=r0+r1
		:"=&r"(a)
		:
		:"r0", "r1"
	);

	printf("a = %d\n", a);
#endif	
	int a, b;

	//除了比较指令和直接操作cpsr的指令，其他指令要影响cpsr标志位就必须加s
	//0x0000000400000005
	//0x00000008ffffffff
	//0x00000d00000004
	asm volatile(
		"mov r0, #5\n"
		"mvn r1, #0\n"//r1=~0;
		"adds %0, r0, r1\n"//cpsr_C=1
		"mov r0, #4\n"
		"mov r1, #8\n"
		"adc %1, r0, r1\n"//%1=r0+r1+C
		:"=&r"(a), "=&r"(b)	
		:
		:"r0", "r1"
	);

	printf("%#010x%08x\n", b, a);

	return 0;
}






