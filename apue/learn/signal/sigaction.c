#include <signal.h>

#include <stdio.h>

static void handler(int signo)
{
	if (signo == SIGINT) {
		printf("Catch SIGINT\n");
	} else if (signo == SIGQUIT) {
		printf("Catch SIGQUIT\n");
	} else {
		printf("error\n");
	}
}

int main(void)
{
	int i;
	struct sigaction act, save;

	//save = signal(SIGINT, handler);
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, &save);

	sigaction(SIGQUIT, &act, NULL);

	while (1) {
		pause();
	}

	return 0;
}
