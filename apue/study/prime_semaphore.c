#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>

#define THREAD_NUM 8

#define START 100000001
#define END   100000100

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static sem_t sem_j;
static sem_t sem_m;

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
		//pthread_mutex_lock(&mutex);

		//while (data == 0) {
        sem_wait(&sem_j);
		//}

		if (data == -1) {
			//pthread_mutex_unlock(&mutex);
			break;
		}

		mydata = data;
		data = 0;

		//pthread_mutex_unlock(&mutex);
		sem_post(&sem_m);
		//printf("%d\n", mydata);

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

    sem_init(&sem_j, 0, 0);
    sem_init(&sem_m, 0, 1);

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_create(tid + i, NULL, jobs, NULL);
	}

	for (i = START; i <= END; i++) {
		//pthread_mutex_lock(&mutex);
		//while (data != 0) {
		sem_wait(&sem_m);
		//}
		data = i;
		//pthread_mutex_unlock(&mutex);
		sem_post(&sem_j);
	}

	//pthread_mutex_lock(&mutex);
	//while (data != 0) {
	sem_wait(&sem_m);
	//}
	data = -1;
	//pthread_mutex_unlock(&mutex);
	for (i = 0; i < THREAD_NUM; i++)//没有broadcast，只能根据线程数目进行post
		sem_post(&sem_j);

	//pthread_exit(NULL);
	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(tid[i], NULL);
	}

    sem_destroy(&sem_m);
    sem_destroy(&sem_j);
	//pthread_mutex_destroy(&mutex);

	printf("\n");
	return 0;
}


