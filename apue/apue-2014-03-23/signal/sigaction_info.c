#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void handler(int signo, siginfo_t *info, void *unuse)
{
	if (signo == SIGINT) {
		printf("Catch SIGINT\n");
	} else if (signo == SIGQUIT) {
		printf("Catch SIGQUIT\n");
	} else {
		printf("Catch other signal\n");
	}
	printf("pid = %d, uid = %d\n", info->si_pid, info->si_uid);
	printf("si_int = %d\n", info->si_int);
}

#define BUFSIZE 32

int main(void)
{
	int i;
	int ret;
	char buf[BUFSIZE];
	struct sigaction act, oact;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = SA_RESTART | SA_SIGINFO;

	sigaction(SIGINT, &act, &oact);
	sigaction(SIGQUIT, &act, &oact);

	for (i = 0; ; i++) {
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
	}

	return 0;
}
