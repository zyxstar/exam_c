#include <stdio.h>

#if 0
	hello.c
	gcc 	hello.c -----> hello.s
	as 	hello.s----->hello.o
	ld 	hello.o---->hello
#endif

//立即数：被编译到指令当中的数据
//立即数：1.本身小于等于255
//	  2.经过循环右移偶数位之后小于等于255
//	  3.按位取反之后符合1或者2
int main(void)
{
	register unsigned int a asm("r0");
	//delay(100);
	asm volatile(
		"mov r0, #10\n"//r0=4
	);

	printf("r0 = %x\n", a);
	
	return 0;
}




