#include <stdio.h>

extern int a;

int main(void)
{
	printf("in main(), a = %d\n", a);

	foo();
	foo();
	foo();

	printf("in main(), a = %d\n", a);

	return 0;
}
