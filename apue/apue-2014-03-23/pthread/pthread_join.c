#include <pthread.h>

#include <stdio.h>

void *jobs(void *data)
{
	printf("in %s(), data = %d\n", __func__, (int)data);

	return data;
}

int main(void)
{
	pthread_t tid[9];
	int i;

	/* fixme */
	int retval;

	for (i = 0; i < 9; i++) {
		pthread_create(&tid[i], NULL, jobs, (void *)i);
	}

	printf("in %s()\n", __func__);

	for (i = 0; i < 9; i++) {
		pthread_join(tid[i], (void **)&retval);
		printf("get return value: %d\n", retval);
	}

	pthread_exit(NULL);

	return 0;
}
