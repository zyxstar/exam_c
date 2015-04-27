#include <stdio.h>

int add(int aa, int bb)
{
	int ccc;
	ccc = aa + bb;
	return ccc;
}

int main(void)
{
	int a, b, c;
	a = 3, b = 7;
	c = add(a, b);

	printf("c = %d\n", c);

	return 0;
}
