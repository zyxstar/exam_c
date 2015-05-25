#include <stdio.h>

int main(void)
{
	//gcc 
	printf("%d\n", (-20) >> 1);
	#if 0
	lsl 逻辑左移
	lsr 逻辑右移
	asr 算术右移   
	ror 循环右移
	#endif
	int lsl, lsr, asr, ror, test1, test2;

	asm volatile(
		"mov r0, #30\n"
		"mov %0, r0, lsl #2\n"
		"mov %1, r0, lsr #1\n"
		"mov %2, r0, asr #1\n"
		"mov r0, #-20\n"
		"mov %4, r0, lsr #1\n"
		"mov %5, r0, asr #1\n"
		"mov r0, #0xff\n"//0xe000001f
		"mov %3, r0, ror #3\n"
		:"=&r"(lsl), "=&r"(lsr), "=&r"(asr), "=&r"(ror), "=&r"(test1), "=&r"(test2)
		:
		:"r0"
	);

	printf("lsl = %d\n", lsl);
	printf("lsr = %d\n", lsr);
	printf("asr = %d\n", asr);
	printf("test1 = %d\n", test1);
	printf("test2 = %d\n", test2);
	printf("ror = %x\n", ror);

	return 0;
}
