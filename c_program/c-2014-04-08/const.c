#include <stdio.h>

int main(void)
{
	const int a = 78;
	int *p = (int *)&a;

	const int *q;
	int const *q;
	int * const q;
	const int * const q;

	*p = 6;
	//a = 6;
	printf("a = %d\n", a);

	return 0;
}
