#include <stdio.h>

int main(void)
{
	int a = 6;
	int *p = &a;

	printf("a = %d\n", *p);
	*p = 7;
	printf("a = %d\n", a);

	return 0;
}
