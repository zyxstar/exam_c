#include <pthread.h>
#include <signal.h>

#include <stdio.h>

static pthread_t tid1, tid_signal;

void *jobs(void *unuse)
{
	while (1) {
		pause();
	}

	return NULL;
}

void *job_signal(void *unuse)
{
	sigset_t set;
	int signo;

        sigemptyset(&set);
	sigaddset(&set, SIGINT);
        sigaddset(&set, SIGQUIT);

	while (1) {
		sigwait(&set, &signo);
		if (signo == SIGINT) {
			printf("Catch SIGINT\n");
		} else if (signo == SIGQUIT) {
			printf("Catch SIGQUIT\n");
		}
	}

	return 0;
}

int main(void)
{
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	pthread_sigmask(SIG_BLOCK, &set, NULL);

	pthread_create(&tid1, NULL, jobs, NULL);
	pthread_create(&tid_signal, NULL, job_signal, NULL);

	while (1) {
		pause();
	}

	return 0;
}
