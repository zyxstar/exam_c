#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int main(void)
{
	int a, b, c;
	int (*p)(int, int);

	a = 3, b = 7;
	p = add;
	c = p(a, b);

	printf("c = %d\n", c);

	return 0;
}
