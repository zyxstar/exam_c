#include <pthread.h>

#include <stdio.h>

void *jobs(void *unuse)
{
	printf("in jobs()\n");
	return NULL;
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, jobs, NULL);

	printf("in main()\n");

	pthread_exit(NULL);
}
