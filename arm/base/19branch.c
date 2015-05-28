#include <stdio.h>

#if 0
	APCS
	arm过程调用标准
	用来约束汇编和C/C++相互调用
	1.传参数  r0, r1, r2, r3 如果参数个数大于4个，那么超过4个的参数放到栈（越靠后的参数越先入栈）
	2.要求必须用满递减栈
	3.返回值  如果返回值是32位则放到r0，如果64位则高32位放到r1,低32位放到r0
#endif

int main(void)
{
	int a;

	//asm volatile(
	//	"mov %0, #3\n"
	//	"b end\n"
	//	"mov %0, #4\n"
	//	"end:\n"
	//	:"=&r"(a)
	//);

	//printf("%d\n", a);

	asm volatile(
		"mov r0, #5\n"
		"mov r1, #6\n"
		"push {r0, r1}\n"
		"mov r0, #1\n"
		"mov r1, #2\n"
		"mov r2, #3\n"
		"mov r3, #4\n"
		"bl nihao\n"//先把下一条指令的地址保存在lr中，然后在跳转
		//pop {r0, r1}
		"add sp, sp, #8\n"
		"mov %0, r0\n"
		:"=&r"(a)::"r0", "r1"
	);

	printf("a = %d\n", a);

	return 0;
}

int nihao(int a, int b, int c, int d, int e, int f)
{
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	printf("e = %d\n", e);
	printf("f = %d\n", f);

	return a + b + c + d + e + f;
}

#if 0
asm (
	"nihao:\n"
	"add r0, r0, r1\n"
//	"mov pc, lr\n"
	"bx lr\n"
);
#endif


