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

#define BUFSIZE 32

int main(void)
{
	int i;
	int ret;
	char buf[BUFSIZE];

	signal(SIGINT, handler);
	//signal(SIGQUIT, handler);

	for (i = 0; ; i++) {

	}

	return 0;
}
