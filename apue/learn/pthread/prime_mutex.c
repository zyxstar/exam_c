/* Never use this style */
/* For lecture */

#include <pthread.h>

#include <stdio.h>

#define THREAD_NUM 6

#define START 100000001
#define END   100000100

static pthread_mutex_t mutex_m = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_j = PTHREAD_MUTEX_INITIALIZER;

static int data;

static int is_prime(int data)
{
	int i;

	for (i = 2; i < data / 2; i++) {
		if (data % i == 0) {
			return 0;
		}
	}
	return 1;
}

static void *jobs(void *unuse)
{
	while (1) {
		pthread_mutex_lock(&mutex_j);
		if (is_prime(data)) {
			printf("%d ", data);
			fflush(stdout);
		}
		pthread_mutex_unlock(&mutex_m);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int i;

	pthread_mutex_lock(&mutex_j);

	for (i = 0; i < 6; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex_m);
		data = i;
		pthread_mutex_unlock(&mutex_j);
	}

	pthread_exit(NULL);

	//pthread_mutex_destroy();
}
