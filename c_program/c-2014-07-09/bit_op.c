#include <stdio.h>

int main(void)
{
	int data = 0xf4a;
	int a, b, c, d;
	a = b = c = d = data;

	/* set bit 3 */
	a = a | (1 << 3);
	printf("a = %x\n", a);

	/* clear bit 3 */
	b = b & ~(1 << 3);
	printf("b = %x\n", b);

	/* invert bit 3 */
	c = c ^ (1 << 3);
	printf("c = %x\n", c);

	/* get bit 3 */
	printf("bit 3 = %d\n", !!(data & (1 << 3)));

	/* set bit 4~7 1001 */
	d &= ~(0xf << 4);
	//d |= (0x9 << 4);
	d |= ((1 << 3 | 1 << 0) << 4);
	printf("d = %x\n", d);

	return 0;
}
