#include <pthread.h>

#include <stdio.h>

#define THREAD_NR 6

#define START     10
#define END       50

static int data = 5;
static pthread_mutex_t mutex_m  =  PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_j  =  PTHREAD_MUTEX_INITIALIZER;

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

void *jobs(void *unuse)
{
	while (1) {
		pthread_mutex_lock(&mutex_j);
		if (is_prime(data)) {
			printf("%d ", data);
			fflush(NULL);
		}
		pthread_mutex_unlock(&mutex_m);
	}

	return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[THREAD_NR];

	pthread_mutex_lock(&mutex_j);

	for (i = 0; i < 6; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex_m);
		data = i;
		pthread_mutex_unlock(&mutex_j);
	}

	while (1) {
		pause();
	}

	return 0;
}
