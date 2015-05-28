#include <stdio.h>

//输出变量是对于汇编而言的，汇编对这个变量只能写不能读

int main(void)
{
	int out;
	int out1;

	asm volatile(
		"mov %0, #3\n"
		"mov %1, #4\n"
		:"=&r"(out), "=&r"(out1)//声明输出变量
		:
		:
	);

	printf("out = %d\n", out);
	printf("out1 = %d\n", out1);

	return 0;
}
