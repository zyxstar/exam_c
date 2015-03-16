#include <signal.h>

#include <stdio.h>

int main(void)
{
	sigset_t set, oset;
	int i;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, &oset);

	for (i = 0; ; i++) {
		if (i == 10) {
			sigprocmask(SIG_SETMASK, &oset, NULL);
		}
		sleep(1);
		printf("i = %d\n", i);
	}

	return 0;
}
