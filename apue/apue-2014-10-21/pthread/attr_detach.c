#include <pthread.h>

#include <stdio.h>
#include <errno.h>

void *job(void *unuse)
{
	printf("in job()\n");
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int ret;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&tid, &attr, job, NULL);
	pthread_attr_destroy(&attr);

	ret = pthread_join(tid, NULL);
	if (ret == EINVAL) {
		printf("detached\n");
	} else {
		printf("joinable\n");
	}

	pthread_exit(NULL);
}
