#include <stdio.h>

int main(void)
{
	const int a = 6;
	int *p = (int *)&a;

	const int *p;
	int const *p;
	int * const p;
	const int * const p;
	int const * const p;

	printf("a = %d\n", a);
	//a = 7;
	*p = 7;
	printf("a = %d\n", a);

	return 0;
}
