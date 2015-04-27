#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
	struct sigaction act, oact;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	//act.sa_flags = SA_RESTART;
	act.sa_flags = 0;

	sigaction(SIGINT, &act, &oact);
	sigaction(SIGQUIT, &act, &oact);

	for (i = 0; ; i++) {
#if 0
		printf("i = %d\n", i);
		sleep(3);
#else
		ret = read(0, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}
		if (ret == -1) {
			perror("read()");
			if (errno == EINTR) {
				continue;
			}
		}
		write(1, buf, ret);
#endif
	}

	return 0;
}
