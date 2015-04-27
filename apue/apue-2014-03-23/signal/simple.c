#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int signo)
{
	if (signo == SIGINT) {
		printf("Catch SIGINT\n");
	} else if (signo == SIGQUIT) {
		printf("Catch SIGQUIT\n");
	} else {
		printf("Catch other signal\n");
	}
}

int main(void)
{
	int i;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	for (i = 0; ; i++) {
		printf("%d\n", i);
		sleep(1);
	}

	return 0;
}
