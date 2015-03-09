#include <stdio.h>

int main(void)
{
	printf("hello");
	fflush(stdout);

	*(int *)4 = 6;

	return 0;
}
