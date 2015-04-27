#include <stdio.h>

inline int add(int a, int b)
{
	return a + b;
}

int main(void)
{
	int a, b, c;

	a = 3, b = 5;
	c = add(a, b);
	printf("c = %d\n", c);

	return 0;
}
