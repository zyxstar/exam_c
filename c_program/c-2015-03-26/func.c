#include <stdio.h>

int abc;

int add(int a, int b)
{
	int c;

	c = a + b;

	return c;
}

int main(void)
{
	int a, b, c;

	a = 4, b = 7;

	c = add(a, b);
	printf("c = %d\n", c);

	return 0;
}
