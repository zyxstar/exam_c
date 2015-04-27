#include <stdio.h>

#include "./a.h"

int a = 10;

void bar(void)
{
	printf("in bar(), a = %d\n", a);
	a += 7;

	printf("in bar(), a = %d\n", a);
}
