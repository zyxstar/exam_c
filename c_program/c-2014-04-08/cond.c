#include <stdio.h>

int main(void)
{
	int a;

	a = (3 < 5 ? 5 + 7 : 2 * 3);
	printf("a = %d\n", a);

	return 0;
}
