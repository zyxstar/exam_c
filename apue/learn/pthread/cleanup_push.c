#include <pthread.h>

#include <stdio.h>

void cleanup(void *str)
{
	printf("in cleanup(), %s\n", str);
}

void *job_return(void *ind)
{
	pthread_cleanup_push(cleanup, "return");
	return NULL;
	pthread_cleanup_pop(0);
}

void *job_exit(void *ind)
{
	pthread_cleanup_push(cleanup, "exit");
	pthread_exit(NULL);
	pthread_cleanup_pop(0);
}

int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, job_return, NULL);
	pthread_create(&tid, NULL, job_exit, NULL);

	pthread_exit(NULL);
}
