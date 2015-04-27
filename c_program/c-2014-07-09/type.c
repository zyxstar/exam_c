#include <stdio.h>

void foo(int a)
{
	printf("%d\n", a);
}

int main(void)
{
	double d = 3.14;

	printf("%f\n", d);
	printf("%d\n", d);
	printf("%d\n", (int)d);
	foo(d);

	return 0;
}
