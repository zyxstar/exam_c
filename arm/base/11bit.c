#include <stdio.h>

#if 0
32位
LEDCON |= 1 << n;

orr LEDCON, LEDCON, 1 << n

LEDCON &= ~(3 << n);

mvn r0, 3 << n
and LEDCON, LEDCON, r0

bic LEDCON, LEDCON, 1 << 3

#endif

int main(void)
{
	//mvn r0, #0\n
	int and, orr, eor, bic, rbit = 0x12345678;

	asm volatile(
		"mov r0, #0xf0\n"
		"mov r1, #0xaa\n"
		//"and r2, r0, r1\n"//r2=r0&r1
		//"and r0, r0, r1\n"//r0=r0&r1
		//"and r0, r1\n"//r0&=r1
		"and %0, r0, r1\n"
		"orr %1, r0, r1\n"
		"eor %2, r0, r1\n"
		"mov r0, #0xff\n"
		"mov r1, #(3 << 2)\n"//1100  3 << 2
		"bic %3, r0, r1\n"//%3=r0&(~r1)
		"rbit %4, %4\n"
		:"=&r"(and), "=&r"(orr), "=&r"(eor), "=r"(bic), "+r"(rbit)
		:
		:"r0", "r1"
	);

	printf("and = %x\n", and);
	printf("orr = %x\n", orr);
	printf("eor = %x\n", eor);
	printf("bic = %x\n", bic);
	printf("rbit = %x\n", rbit);

	return 0;
}



