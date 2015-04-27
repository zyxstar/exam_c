#include <stdio.h>

int main(void)
{
	int a, b, c, d;

	a = b = c = d = 123;

	a = a | (1 << 3);
	printf("a = %d\n", a);

	b = b & ~(1 << 3);
	printf("b = %d\n", b);

	c = c ^ (1 << 3);
	printf("c = %d\n", c);

	if (d & (1 << 3)) {
		printf("bit 3 is 1\n");
	} else {
		printf("bit 3 is 0\n");
	}

	printf("bit 3 is %d\n", !!(d & (1 << 3)));

	return 0;
}
