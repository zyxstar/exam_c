#include <stdio.h>

int main(void)
{
	int a = 0x12345678;

	//htonl  ntohl
	asm volatile(
		"rev %0, %0\n"
		:"+r"(a)
	);

	printf("a = %x\n", a);

	a = 0x1234;
	//htons ntohs
	asm volatile(
		"rev16 %0, %0\n"
		:"+r"(a)
	);

	printf("a = %x\n", a);

	return 0;
}
