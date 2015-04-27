#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *p;

	p = malloc(sizeof(*p));
	if (p == NULL) {
		printf("malloc() failed.\n");
		return 1;
	}

	*p = 123;

	free(p);

	return 0;
}
