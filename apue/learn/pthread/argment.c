#include <pthread.h>

#include <stdio.h>

#define THREAD_NUM 9

void *jobs(void *ind)
{
	printf("in jobs(), ind = %d\n", (int)ind);
	return NULL;
}

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int i;

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_create(tid + i, NULL, jobs, (void *)i);
	}

	printf("in main()\n");

	pthread_exit(NULL);
}
