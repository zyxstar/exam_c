#include <signal.h>

#include <stdio.h>

void handler(int unuse)
{
	printf("Catch SIGINT\n");
}

int main(void)
{
	int i;

	signal(SIGINT, handler);

	for (i = 0; ; i++) {
		sleep(2);
		printf("hehe, i = %d\n", i);
	}

	return 0;
}
