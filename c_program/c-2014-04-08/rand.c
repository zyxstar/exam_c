#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;

	srand(getpid());

	for (i = 0; i < 5; i++) {
		printf("%d\n", rand());
	}

	return 0;
}
