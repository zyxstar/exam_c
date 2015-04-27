#include <pthread.h>

#include <stdio.h>

#define THREAD_NR 5

static void *jobs(void *ind)
{
	printf("in jobs(), ind = %d\n", (int)ind);

	return (void *)((int)ind * 100);
}

int main(void)
{
	pthread_t tid[THREAD_NR];
	int i;
	void *val;

	printf("before\n");

	for (i = 0; i < THREAD_NR; i++) {
		pthread_create(tid + i, NULL, jobs, (void *)i);
	}

	printf("after\n");

	for (i = 0; i < THREAD_NR; i++) {
		pthread_join(tid[i], &val);
		printf("tid[%d] return %d\n", i, (int)val);
	}
	pthread_exit(NULL);

	//return 0;
}
