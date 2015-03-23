#include <signal.h>

#include <stdio.h>

static void handler(int unuse)
{
	printf("Catch SIGINT\n");
}

#define BUFSIZE 32

int main(void)
{
	struct sigaction act;
	int ret;
	char buf[BUFSIZE];

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	//act.sa_flags = SA_RESTART;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);

	while (1) {
		ret = read(0, buf, BUFSIZE);
		printf("ret = %d\n", ret);
	}

	return 0;
}
