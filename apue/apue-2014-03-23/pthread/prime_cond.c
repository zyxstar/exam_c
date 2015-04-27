#include <pthread.h>

#include <stdio.h>

#define THREAD_NR 6

#define START     10
#define END       50

static int data = 0;
static pthread_mutex_t mutex  =  PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_m = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_j = PTHREAD_COND_INITIALIZER;

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
	int mydata;

	while (1) {
		pthread_mutex_lock(&mutex);
		while (data == 0) {
			pthread_cond_wait(&cond_j, &mutex);
		}
		if (data == -1) {
			pthread_mutex_unlock(&mutex);
			break;
		}
		mydata = data;
		data = 0;
		pthread_cond_signal(&cond_m);
		pthread_mutex_unlock(&mutex);

		if (is_prime(mydata)) {
			printf("%d ", mydata);
			fflush(NULL);
		}
	}

	return NULL;
}

int main(void)
{
	int i;
	pthread_t tid[THREAD_NR];

	for (i = 0; i < 6; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex);
		while (data != 0) {
			pthread_cond_wait(&cond_m, &mutex);
		}
		data = i;
		pthread_cond_signal(&cond_j);
		pthread_mutex_unlock(&mutex);
	}

	pthread_mutex_lock(&mutex);
	while (data != 0) {
		pthread_cond_wait(&cond_m, &mutex);
	}
	data = -1;
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond_j);

	for (i = 0; i < 6; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("\n");

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_j);
	pthread_cond_destroy(&cond_m);

	return 0;
}
