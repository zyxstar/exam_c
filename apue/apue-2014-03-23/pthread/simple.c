#include <pthread.h>

#include <stdio.h>

void *jobs(void *data)
{
	printf("in %s(), data = %d\n", __func__, (int)data);

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int i;

	for (i = 0; i < 9; i++) {
		pthread_create(&tid, NULL, jobs, (void *)i);
	}

	printf("in %s()\n", __func__);

	pthread_exit(NULL);

	return 0;
}
