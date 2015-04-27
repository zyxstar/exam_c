#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int main(void)
{
	int a = 3, b = 6, c;
	int (*p)(int, int);

	p = add;
	c = p(a, b);
	printf("c = %d\n", c);

	return 0;
}
