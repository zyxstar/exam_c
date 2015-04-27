#include <stdio.h>

int main(void)
{
	printf("hello ");
	//fflush(stdout);
	fflush(NULL);
	*(int *)4 = 6;
	printf("will return\n");

	return 0;
}
