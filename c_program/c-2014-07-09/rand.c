#include <stdio.h>

int main(void)
{
	int i;

	srand(32167);

	for (i = 0; i < 10; i++) {
		printf("%d ", rand());
	}
	printf("\n");

	return 0;
}
