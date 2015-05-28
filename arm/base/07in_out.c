#include <stdio.h>

#if 0
=:代表输出变量
r:操作方式是寄存器
+:代表输入输出变量
&:代表输出变量不和输入变量共用寄存器

第三个冒号用来保护显式使用过的寄存器
#endif

int main(void)
{
	int a = 1, b = 2, c = 3;
	int d, e, f;
	int hello = 5;
	int nihao;

	asm volatile(
		//mov r0, ip
		//mov r1, r4
		//mov r2, r5
		//mov r3, r6
		//
		//mov r7, r0
		//mov r6, r1
		//mov r5, r2
		//mov r4, r3
		"mov r0, %4\n"
		"mov r1, %5\n"
		"mov r2, %6\n"
		"mov r3, %7\n"

		"mov %0, r0\n"
		"mov %1, r1\n"
		"mov %2, r2\n"
		"mov %3, r3\n"
		:"=&r"(d), "=&r"(e), "=&r"(f), "=&r"(nihao)
		:"r"(a), "r"(b), "r"(c), "r"(hello)
		:"r0", "r1", "r2", "r3"
	);

	return 0;
}
