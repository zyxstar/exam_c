#include <stdio.h>

int add(int a, int b)
{
	int c;
	c = a + b;

	return c;
}

int main(void)
{
	int a, b, c;

	b = 3; c = 4;
	a = add(b, c);

	printf("a = %d\n", a);

	return 0;
}
