#include <stdio.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{
	int a, b;

	a = 3, b = 5;
	swap(&a, &b);

	printf("a = %d, b = %d\n", a, b);

	return 0;
}
