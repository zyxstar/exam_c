#include <stdio.h>

int main(void)
{
	/* clear */
	printf("\033[2J");

	/* position */
	printf("\033[1;1Hxxx\n");
	printf("\033[5;8H");

	/* color */
	//printf("\033[31m\033[44mhello\033[0m\n");
	printf("\033[31;44mhello\033[0m\n");

	return 0;
}
