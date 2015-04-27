#include <stdio.h>

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	printf("in swap(), a = %d, b = %d\n", *a, *b);
}

int main(void)
{
	int a = 3, b = 6;

	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);

	return 0;
}
