#include <stdio.h>

int main(void)
{
	int a, b, c, d, e, f;

	a = b = c = d = e = f = 1234567 + 8;
	//a = b = c = d = e = f = 1234567;
	/* 100101101011010000111 */

	printf("%d\n", !!(a & (1 << 3)));

	b |= 1 << 3;
	printf("%d\n", b);

	c &= ~(1 << 3);
	printf("%d\n", c);

	d ^= 1 << 3;
	printf("%d\n", d);

	/* set 15:12 1010 */
	e &= ~(0xf << 12);
	e |= (1 << 15) | (0 << 14) | (1 << 13) | (0 << 12);
	//e |= 0xa << 12;
	printf("%d\n", e);
	/* 100101101011010001111 */
	/* 100101010011010001111 */

/*
	printf("a & 10100010 = %d\n", a & 162);
	printf("a | 10100010 = %d\n", a | 162);
	printf("a ^ 10100010 = %d\n", a ^ 162);
	printf("a << 3 = %d\n", a << 3);
	printf("a >> 3 = %d\n", a >> 3);
	printf("~a = %d\n", ~a);
*/
	return 0;
}
