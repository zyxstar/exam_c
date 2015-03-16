#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void bar1(void)
{
	printf("%s\n", __func__);
}

void bar2(void)
{
	printf("%s\n", __func__);
}

void foo(void)
{
	printf("%s 1", __func__);
	//return;
	exit(4);
	printf("%s 2\n", __func__);
}

int main(void)
{
	atexit(bar1);
	atexit(bar2);

	printf("%s 1\n", __func__);
	foo();
	printf("%s 2\n", __func__);

	return 0;
}
