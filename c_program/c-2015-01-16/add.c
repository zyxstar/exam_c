#include <stdio.h>

int add(int aa, int bb)
{
	int cc;

	cc = aa + bb;

	return cc;
}

int main(void)
{
	int a, b, c;

	a = 3; b = 8;
	//c = a + b;
	c = add(a, b);

	printf("c = %d\n", c);

	return 0;
}
