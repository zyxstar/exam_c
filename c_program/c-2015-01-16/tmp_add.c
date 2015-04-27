#include <stdio.h>

int add(int a, int b)
{
	int c;
	c = a + b;
	return c;
}

int main(void)
{
	int a;

	a = add(123, 456);
	printf("a = %d\n", a);

	return 0;
}
