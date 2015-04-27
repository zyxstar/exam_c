#include <stdio.h>

int main(void)
{
	int *p = NULL;
	int a;
	double d;

	p = &a;
	*p = 123;

	printf("a = %d\n", a);

	d = 7.0;
	p = &d;
	printf("*p = %d\n", *p);

	*p = 2000000000;
	printf("d = %f\n", d);

	return 0;
}
