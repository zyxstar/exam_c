#include <stdio.h>

int main(void)
{
	int a, b, c, d, bit;

	a = b = c = d = 32175;

	/* set */
	a = a | (1 << 3);
	printf("a = %d\n", a);

	/* clear */
	b = b & ~(1 << 3);
	printf("b = %d\n", b);

	/* reverse */
	c = c ^ (1 << 3);
	printf("c = %d\n", c);

	/* get */
	//bit = d & (1 << 3);
	bit = !!(d & (1 << 3));
	printf("bit 3 = %d\n", bit);

	return 0;
}
