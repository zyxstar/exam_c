#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a;

	srand(getpid());

	while (1) {
		sleep(1);
		a = rand();
		printf("%d ", a);
		fflush(NULL);
	}

	return 0;
}
