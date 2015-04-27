#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

void foo(void)
{
	printf("in foo(): xxx");
	//fflush(stdout);
	//_exit(123);
	exit(123);
	printf("in foo(): yyy\n");
}

static void bar1(void)
{
	printf("call %s()\n", __func__);
}

static void bar2(void)
{
	printf("call %s()\n", __func__);
}

int main(void)
{
	atexit(bar1);
	atexit(bar2);
	atexit(bar2);

	printf("xxx\n");

	foo();

	printf("yyy\n");

	exit(6);

	printf("zzz\n");

	return 0;
}
