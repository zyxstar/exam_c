#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("\033[31mmain() 1\033[0m\n");

	system("ls -l");

	printf("\033[31mmain() 2\033[0m\n");

	return 0;
}
