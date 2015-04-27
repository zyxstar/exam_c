#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

void foo(void)
{
	printf("foo 1");
	exit(6);
	printf("foo 2\n");
}

void func1(void)
{
	printf("func1\n");
}

void func2(void)
{
	printf("func2\n");
}

int main(void)
{
	atexit(func1);
	atexit(func1);
	atexit(func2);

	printf("main 1\n");

	foo();

	printf("main 2\n");

	exit(123);

	printf("main 3\n");

	return 0;
}
