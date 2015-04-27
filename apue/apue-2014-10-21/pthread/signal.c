#include <pthread.h>
#include <signal.h>

#include <stdio.h>

void *job1(void *unuse)
{
	while (1) {
		sleep(3);
		printf("in %s()\n", __func__);
	}
	return NULL;
}

void *job2(void *unuse)
{
	while (1) {
		sleep(3);
		printf("in %s()\n", __func__);
	}
	return NULL;
}

void *job_signal(void *unuse)
{
	sigset_t set;
	int sig;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGUSR1);

	while (1) {
		sigwait(&set, &sig);
		if (sig == SIGINT) {
			printf("Catch SIGINT\n");
		} else if (sig == SIGUSR1) {
			printf("Catch SIGUSR1\n");
		}
	}

	return NULL;
}

int main(void)
{
	pthread_t tid[3];
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGUSR1);
	pthread_sigmask(SIG_BLOCK, &set, NULL);

	pthread_create(tid, NULL, job1, NULL);
	pthread_create(tid + 1, NULL, job2, NULL);
	pthread_create(tid + 2, NULL, job_signal, NULL);

	while (1) {
		sleep(3);
		printf("in %s()\n", __func__);
	}

	return 0;
}
