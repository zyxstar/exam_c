#include <stdio.h>

#if 0
	int a = 5;
	int b = 6;
	int c;
	
	if(a > b)      cmp a,b   a - b NZ  N=1 Z=0
		c = 7;  大于  N==0 Z==0
		movgt c, #7
	else if(a == b)
		c = 9;  等于  Z==1
		moveq c, #9
	else
		c = 10; 小于 N==1
		movlt c, #10

	mov[cond]
	cond:ne eq lt gt le ge 
#endif

int main(void)
{
	int a;

	asm volatile(
		"mov r0, #5\n"
		"mov r1, #6\n"
		"cmp r0, r1\n"
		"moveq %0, #1\n"
		"movne %0, #2\n"
		"movlt %0, #3\n"
		"movgt %0, #4\n"
		:"=&r"(a)
		::"r0", "r1"
	);

	printf("a = %d\n", a);

	return 0;
}
