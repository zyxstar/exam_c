#include <pthread.h>
#include <signal.h>

#include <stdio.h>

void *job_normal(void *unuse)
{
	printf("in %s(), %p\n", __func__, (void *)pthread_self());

	while (1) {
		pause();
		printf("pause() return");
	}
	return NULL;
}

#if 0
void *job_signal(void *unuse)
{
	sigset_t set;
	int signo;

        sigemptyset(&set);
        sigaddset(&set, SIGINT);

	while (1) {
		sigwait(&set, &signo);
		if (signo == SIGINT) {
			printf("Catch SIGINT\n");
		}
	}

	return NULL;
}
#else
void handler(int unuse)
{
	printf("Catch SIGINT, %p\n", (void *)pthread_self());
}

void *job_signal(void *unuse)
{
	sigset_t set;

	printf("in %s(), %p\n", __func__, (void *)pthread_self());

	signal(SIGINT, handler);

        sigemptyset(&set);
        sigaddset(&set, SIGINT);
	pthread_sigmask(SIG_UNBLOCK, &set, NULL);

	while (1) {
		pause();
		printf("in %s()\n", __func__);
	}

	return NULL;
}
#endif

int main(void)
{
	pthread_t tid[2];
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	pthread_sigmask(SIG_BLOCK, &set, NULL);

	pthread_create(tid, NULL, job_normal, NULL);
	pthread_create(tid + 1, NULL, job_signal, NULL);

	printf("in %s(), %p\n", __func__, (void *)pthread_self());

	while (1) {
		pause();
		printf("pause() return");
	}

	return 0;
}
