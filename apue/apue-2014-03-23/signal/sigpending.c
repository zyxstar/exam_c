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
	sigset_t set, oset, pset;

	signal(SIGINT, handler);
	//signal(SIGQUIT, handler);

	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, &oset);

	for (i = 0; ; i++) {
		if (i == 10) {
			sigprocmask(SIG_UNBLOCK, &set, NULL);
		}
		sigpending(&pset);
		if (sigismember(&pset, SIGINT)) {
			printf("SIGINT pending\n");
		}
		if (sigismember(&pset, SIGQUIT)) {
                        printf("SIGQUIT pending\n");
                }
		printf("%d\n", i);
		sleep(3);
	}

	sigprocmask(SIG_SETMASK, &oset, NULL);

	return 0;
}
