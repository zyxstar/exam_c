#include <pthread.h>

#include <stdio.h>

#define THREAD_NUM 8

static int data = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *jobs(void *unuse)
{
	int i;

	for (i = 0; i < 10000; i++) {
		pthread_mutex_lock(&mutex);
		data++;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int i;

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mutex);

	printf("data = %d\n", data);

	return 0;
}
