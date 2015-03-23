#include <signal.h>
#include <pthread.h>

#include <stdio.h>

static void handler(int signo)
{
	printf("%s %p\n", __func__, (void *)pthread_self());

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
	printf("%s %p\n", __func__, (void *)pthread_self());

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
