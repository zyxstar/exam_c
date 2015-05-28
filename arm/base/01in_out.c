#include <stdio.h>

int main(void)
{
	register unsigned int a asm("sp");
	register unsigned int b asm("sp");

	printf("sp = %x\n", a);
	printf("sp = %x\n", b);
	
	a = 0;

	printf("sp = %x\n", b);

	return 0;
}
