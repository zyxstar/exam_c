#include <stdio.h>

union foo {
	int a;
	char c;
	double d;
};

int main(void)
{
	union foo b = {123};

	b.a = 0x303132;
	printf("b.c = %x\n", b.c);

	return 0;
}
