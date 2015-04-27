#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *a;

	a = malloc(sizeof(*a));
	if (a == NULL) {
		...;
	}

	*a = 66;

	free(a);

	return 0;
}
