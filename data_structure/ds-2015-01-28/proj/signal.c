#include <signal.h>

#include <stdio.h>

void handler(int unuse)
{
	printf("Catch signal\n");
}

int main(void)
{
	int i;

	signal(SIGINT, handler);

	for (i = 0; ; i++) {
		sleep(3);
		printf("i = %d\n", i);
	}

	return 0;
}
