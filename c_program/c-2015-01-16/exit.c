#include <stdio.h>
#include <stdlib.h>

void foo(void)
{
	printf("in foo() 1\n");

	exit(7);

	printf("in foo() 2\n");

	return;

	printf("in foo() 3\n");
}

int main(void)
{
	printf("in main() 1\n");

	foo();

	printf("in main() 2\n");

	exit(4);

	printf("in main() 3\n");

	return 0;
}
