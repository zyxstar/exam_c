#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int main(void)
{
	int a, b, c;
	int (*p)(int, int);

	p = add;
	b = 4; c = 3;
	a = p(b, c);

	printf("a = %d\n", a);

	return 0;
}
