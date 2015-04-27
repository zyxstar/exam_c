#include <stdio.h>

int main(void)
{
	int *arr;
	int *tmp;

	arr = malloc(sizeof(int) * 6);
	/* if error */

	tmp = realloc(arr, sizeof(int) * 8);
	if (tmp == NULL) {

	}
	arr = tmp;

	free(arr);

	return 0;
}
