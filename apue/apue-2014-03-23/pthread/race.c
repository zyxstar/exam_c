#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *jobs(void *unuse)
{
	int value;
	char buf[BUFSIZE];
	FILE *fp;
	int i;
	int ret;

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("tmp");
		return NULL;
	}

	for (i = 0; i < 1000; i++) {
		fseek(fp, 0, SEEK_SET);

		pthread_mutex_lock(&mutex);

		ret = fread(buf, 1, BUFSIZE, fp);
		if (ret == 0) {
			//perror("fread()");
			break;
		}
		buf[ret] = '\0';
		value = atoi(buf);
		value++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", value);
		fflush(fp);

		pthread_mutex_unlock(&mutex);
	}

	fclose(fp);

	return NULL;
}

#define THREAD_NR 4

int main(void)
{
	int i;
	pthread_t tid[THREAD_NR];
	int ret;

	for (i = 0; i < THREAD_NR; i++) {
		ret = pthread_create(tid + i, NULL, jobs, NULL);
		if (ret) {
			fprintf(stderr, "pthread_create(): %s\n", strerror(ret));
			return 1;
		}
	}

	for (i = 0; i < THREAD_NR; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}
