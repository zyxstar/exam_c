#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	srand(getpid());

	while (1) {
		printf("%d\n", rand());
		sleep(1);
	}

	return 0;
}
