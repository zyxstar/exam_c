#include <signal.h>

#include <stdio.h>

static void handler(int signo, siginfo_t *info, void *unuse)
{
	if (signo == SIGINT) {
		printf("Catch SIGINT, ");
	} else if (signo == SIGQUIT) {
		printf("Catch SIGQUIT, ");
	} else {
		printf("error\n");
	}

	printf("val = %d\n", info->si_int);
}

int main(void)
{
	int i;
	struct sigaction act, save;

	//save = signal(SIGINT, handler);
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &act, &save);

	sigaction(SIGQUIT, &act, NULL);

	while (1) {
		pause();
	}

	return 0;
}
