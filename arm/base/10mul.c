#include <stdio.h>

int main(void)
{
#if 0
	int a;

	asm volatile(
		"mov r0, #5\n"
		"mov r1, #6\n"
		"mul %0, r0, r1\n"//%0=r0*r1
		:"=&r"(a)
		:
		:"r0", "r1"
	);

	printf("a = %d\n", a);
#endif
#if 0        
	i = 0;
	c =  M    i * i
	     i<100

	r2 = r2 + r0 * r0

	i = 0;
	while(i < 100)
	mla r2, r0, r0, r2
	i++;
#endif	
	int a;

	asm volatile(
		"mov r0, #3\n"
		"mov r1, #4\n"
		"mov r2, #5\n"
		//"mla %0, r0, r1, r2\n"//%0=r2+r0*r1
		"mls %0, r0, r1, r2\n"//%0=r2-r0*r1
		:"=&r"(a)
		:
		:"r0", "r1", "r2"
	);

	printf("a = %d\n", a);

	return 0;
}






