#include <signal.h>

#include <stdio.h>

int main(void)
{
	sigset_t set, oset, pend;
	int i;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, &oset);

	for (i = 0; ; i++) {
		if (i == 10) {
			sigprocmask(SIG_SETMASK, &oset, NULL);
		}
		sleep(1);
		sigpending(&pend);
		if (sigismember(&pend, SIGINT)) {
			printf("i = %d, SIGINT pending\n", i);
		} else {
			printf("i = %d\n", i);
		}
	}

	return 0;
}
