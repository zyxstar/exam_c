#include <stdio.h>

union {
	struct foo {
		unsigned int a : 1;
		unsigned int b : 2;
		unsigned int c : 3;
		unsigned int d : 1;
	} foo;
	unsigned int xxx;
} x;

int main(void)
{
	x.xxx = 0;
	x.foo.a = 1;
	x.foo.b = 2;
	x.foo.c = 5;
	x.foo.d = 6;
	/* 101101 */

	printf("%d\n", x.xxx);

	return 0;
}
