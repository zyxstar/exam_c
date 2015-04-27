#include <stdio.h>

extern int a;
int a = 0;

void foo(void)
{
	a++;
	printf("a = %d\n", a);
}

