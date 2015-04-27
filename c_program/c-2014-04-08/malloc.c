#include <stdio.h>

int main(void)
{
	int *p;

	p = malloc(sizeof(int));
	if (p == NULL) {
		printf("malloc() failed\n");
		return 1;
	}

	*p = 6;

	free(p);

	return 0;
}
