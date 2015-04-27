#include <stdio.h>

static int aa;

void foo(void)
{
	static int a = 3;
	a++;
	printf("a = %d\n", a);
}

int main(void)
{
	foo();
	foo();
	foo();

	return 0;
}
