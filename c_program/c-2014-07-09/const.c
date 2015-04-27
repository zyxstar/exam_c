#include <stdio.h>

int main(void)
{
	const int a = 5;
	int *p = (int *)&a;

	const int *x;
	int const *x;
	int * const x;
	const int * const x;
	int const * const x;

	printf("a = %d\n", a);

	*p = 123;

	printf("a = %d\n", a);

	return 0;
}
