#include <stdio.h>

int main(void)
{
	const int a = 33;
	int *p = (int *)&a;

	//a = 6;
	*p = 7;
	printf("a = %d\n", a);

	return 0;
}
