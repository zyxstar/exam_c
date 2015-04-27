#include <stdio.h>

int main(void)
{
	printf("\033[2J\033[2;5H\033[31m\033[42mhello\033[0m\n");

	return 0;
}
