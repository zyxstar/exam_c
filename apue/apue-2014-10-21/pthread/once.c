#include <pthread.h>

#include <stdio.h>

static pthread_once_t once_control = PTHREAD_ONCE_INIT;

void once(void)
{
	printf("in once()\n");
}

void *jobs(void *unuse)
{
	pthread_once(&once_control, once);

	printf("in jobs()\n");

	return NULL;
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, jobs, NULL);
	pthread_create(&tid, NULL, jobs, NULL);
	pthread_create(&tid, NULL, jobs, NULL);

	pthread_exit(NULL);
}
