#include <pthread.h>

#include <stdio.h>

#define PLUS_TIMES  100000
#define THREAD_NR   6

static volatile int data = 1;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *jobs(void *unuse)
{
	int i;
	int ret;

	for (i = 0; i < PLUS_TIMES; i++) {
		ret = pthread_mutex_lock(&mutex);
		if (ret) {
			fprintf(stderr, "pthread_mutex_lock() failed, error num = %d\n", ret);
			break;
		}
		data++;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[THREAD_NR];

	for (i = 0; i < THREAD_NR; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = 0; i < THREAD_NR; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	printf("data = %d\n", data);

	return 0;
}
