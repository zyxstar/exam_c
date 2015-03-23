#include <pthread.h>

#include <stdio.h>

#define THREAD_NUM 8

#define START 100000001
#define END   100000100

static pthread_cond_t cond_m = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_j = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int data = 0;

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
	int mydata;

	while (1) {
		pthread_mutex_lock(&mutex);
#if 0
		{
			unlock(&mutex);
			wait(&cond_j);
			lock(&mutex);
		}
#else
		while (data == 0) {
			pthread_cond_wait(&cond_j, &mutex);
		}
#endif
		if (data == -1) {
			pthread_mutex_unlock(&mutex);
			break;
		}

		mydata = data;
		data = 0;

		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond_m);

		if (is_prime(mydata)) {
			printf("%d ", mydata);
			fflush(stdout);
		}
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

	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mutex);
		while (data != 0) {
			pthread_cond_wait(&cond_m, &mutex);
		}
		data = i;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond_j);
	}
	pthread_mutex_lock(&mutex);
	while (data != 0) {
		pthread_cond_wait(&cond_m, &mutex);
	}
	data = -1;
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond_j);

	//pthread_exit(NULL);
	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_cond_destroy(&cond_m);
	pthread_cond_destroy(&cond_j);
	pthread_mutex_destroy(&mutex);

	printf("\n");
	return 0;
}
