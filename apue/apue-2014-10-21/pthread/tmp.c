#include <pthread.h>

#include <stdio.h>

#define START         100000001
#define END           100000100
#define THREAD_NR     8

static volatile int data;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_m = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_j = PTHREAD_COND_INITIALIZER;

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
	int d;

	while (1) {
		pthread_mutex_lock(&mutex);

		while (data == 0) {
			pthread_cond_wait(&cond_j, &mutex);
		}
		if (data < 0) {
			pthread_mutex_unlock(&mutex);
			break;
		}

		d = data;
		if (is_prime(d)) {
			printf("%d ", d);
			fflush(NULL);
		} else {
			printf("\033[31m%d\033[0m ", d);
			fflush(NULL);
		}
		data = 0;
		pthread_mutex_unlock(&mutex);	

		pthread_cond_signal(&cond_m);

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

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex);
		while (data > 0) {
			pthread_cond_wait(&cond_m, &mutex);
		}
		data = i;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond_j);
	}

	pthread_mutex_lock(&mutex);
	while (data > 0) {
		pthread_cond_wait(&cond_m, &mutex);
	}
	data = -1;
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond_j);

	for (i = 0; i < THREAD_NR; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("\n");

	return 0;
}
