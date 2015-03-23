#include <pthread.h>

#include <stdio.h>

#define THREAD_NUM 9

void *jobs(void *ind)
{
	printf("in jobs(), ind = %d\n", (int)ind);
	return (void *)((int)ind + 100);

	/* bug */
	struct {
		int xx, yy, zz;
	} xxx;
	xxx.xx = 3; xxx.yy = 2; xxx.zz = 6;
	return &xxx;
}

int main(void)
{
	pthread_t tid[THREAD_NUM];
	int i;
	void *val;

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_create(tid + i, NULL, jobs, (void *)i);
	}

	printf("in main()\n");

	for (i = 0; i < THREAD_NUM; i++) {
		pthread_join(tid[i], &val);
		printf("val = %d\n", val);
        }

	pthread_exit(NULL);
}
