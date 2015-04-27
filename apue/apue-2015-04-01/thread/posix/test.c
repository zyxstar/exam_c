#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define PNUM 1000

int num = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *p_jobs(void *p)
{
	pthread_mutex_lock(&mutex);
	num++;

	switch(num % 4)
	{
		case 1:
			printf("a");
			break;
		case 2:
			printf("b");
			break;
		case 3:
			printf("c");
			break;
		case 0:
			printf("d");
			break;
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(void)
{
	int i;
	pthread_t tid[PNUM];
	
	for(i = 0; i < PNUM; i++)
	{
		pthread_create(tid + i, NULL, p_jobs, NULL);
	}
	for(i = 0; i < PNUM; i++)
	{
		pthread_join(*(tid + i) , NULL);
	}

	exit(0);
}
