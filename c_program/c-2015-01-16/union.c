#include <stdio.h>

union {
	int a;
	char c;
	double d;
} foo;

int main(void)
{
	printf("%p, %p, %p\n", &foo.a, &foo.c, &foo.d);
	foo.a = 0x303132;
	printf("foo.a = %x\n", foo.a);
	printf("foo.c = %x\n", foo.c);

	return 0;
}
