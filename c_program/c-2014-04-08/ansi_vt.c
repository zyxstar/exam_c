#include <stdio.h>

int main(void)
{
	printf("\033[2J\033[10;3H");
	printf("\033[31;42mhello\033[0m\n");

	return 0;
}
