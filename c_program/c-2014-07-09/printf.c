#include <stdio.h>

int foo(void)
{
	printf("12345\n");
}

int main(void)
{
	int a;

	a = foo();

	printf("a = %d\n", a);
	return 0;
}
