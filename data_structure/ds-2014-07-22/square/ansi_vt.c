#include <stdio.h>

int main(void)
{
	printf("\033[2J");	/* clear */
	printf("\033[3;5H");	/* coordinate */
	//printf("\033[31m\033[44mhello\033[0m\n");
	printf("\033[31;44mhello\033[0m\n"); /* color */

	return 0;
}
