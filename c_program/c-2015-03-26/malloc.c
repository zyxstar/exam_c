#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *p;
	int i;

	p = malloc(sizeof(int) * 16);
	if (p == NULL) {
		printf("malloc() failed.\n");
		return 1;
	}

	p[1] = 60;
	for (i = 0; i < 16; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");

	free(p);

	return 0;
}
