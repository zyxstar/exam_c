#include <pthread.h>

#include <stdio.h>

void clean1(void *str)
{
	printf("%s:%s\n", __func__, str);
}

void clean2(void *str)
{
	printf("%s:%s\n", __func__, str);
}

void *job1(void *unuse)
{
	pthread_cleanup_push(clean1, (void *)__func__);
	pthread_cleanup_push(clean2, (void *)__func__);

	return NULL;

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	return NULL;
}

void *job2(void *unuse)
{
	pthread_cleanup_push(clean1, (void *)__func__);
	pthread_cleanup_push(clean2, (void *)__func__);

	pthread_exit(NULL);

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);

	return NULL;
}

int main(void)
{
	pthread_t tid[2];

	pthread_create(tid, NULL, job1, NULL);
	pthread_create(tid + 1, NULL, job2, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
