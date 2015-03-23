#include <signal.h>
#include <unistd.h>

#include <stdio.h>

void handler(int unuse)
{
	printf("Catch SIGINT\n");
}

int main(void)
{
	sigset_t set, save, tmp, unblock;

	signal(SIGINT, handler);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_UNBLOCK, &set, &save);
	sigprocmask(SIG_BLOCK, &set, &unblock);

	while (1) {
#if 0
		sigprocmask(SIG_SETMASK, &unblock, &tmp);
		pause();
		sigprocmask(SIG_SETMASK, &tmp, NULL);
#else
		sigsuspend(&unblock);
#endif
		printf("pause() return\n");
		sleep(3);
		printf("sleep() return\n");
	}
	sigprocmask(SIG_SETMASK, &save, NULL);

	return 0;
}
