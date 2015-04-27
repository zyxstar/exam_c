#include <stdio.h>
#include <stdlib.h>

void foo(void)
{
	printf("%s() 1", __func__);
	exit(0);
	//_Exit(0);
	printf("%s() 2\n", __func__);
}

int main(void)
{
	printf("%s() 1\n", __func__);
	foo();
	printf("%s() 2\n", __func__);

	return 0;
}
