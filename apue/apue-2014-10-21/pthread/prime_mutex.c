#include <pthread.h>

#include <stdio.h>

#define START         10000001
#define END           10000100
#define THREAD_NR     8

static volatile int data;
static pthread_mutex_t mutex_m = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_j = PTHREAD_MUTEX_INITIALIZER;

static int is_prime(int d)
{
	int i;

	for (i = 2; i < d / 2; i++) {
		if (d % i == 0) {
			return 0;
		}
	}
	return 1;
}

void *jobs(void *unuse)
{
	while (1) {
		pthread_mutex_lock(&mutex_j);
		if (is_prime(data)) {
			printf("%d ", data);
			fflush(NULL);
		} else {
			printf("\033[31m%d\033[0m ", data);
			fflush(NULL);
		}
		pthread_mutex_unlock(&mutex_m);	
	}
}

int main(void)
{
	int i;
	pthread_t tid[THREAD_NR];

	pthread_mutex_lock(&mutex_j);

	for (i = 0; i < THREAD_NR; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex_m);
		data = i;
		pthread_mutex_unlock(&mutex_j);
	}

	for (i = 0; i < THREAD_NR; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
