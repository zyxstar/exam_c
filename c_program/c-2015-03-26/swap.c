#include <stdio.h>

void swap(int *aa, int *bb)
{
	int tmp;

	tmp = *aa;
	*aa = *bb;
	*bb = tmp;
}

int main(void)
{
	int a = 4, b = 6;

	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);

	return 0;
}
