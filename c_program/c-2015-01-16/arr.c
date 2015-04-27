#include <stdio.h>

int main(void)
{
	int a[130] = {[5] = 32167, [127] = 12345,};
	int i;

	//a[127] = 123;
	printf("0: %d, 1: %d, 55: %d, 128: %d\n", a[0], a[1], a[55], a[128]);
	printf("5: %d, 127: %d\n", a[5], a[127]);

	return 0;
}
