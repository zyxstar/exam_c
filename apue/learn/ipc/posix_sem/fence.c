#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define PROC_NUM   6

static void jobs(int ind)
{
	int i;
	sem_t *self, *parent;
	char name_self[16];
	char name_parent[16];

	snprintf(name_self, 16, "mysem%d", ind);
	self = sem_open(name_self, 0);
	/* if error */

	snprintf(name_parent, 16, "mysem%d", PROC_NUM);
	parent = sem_open(name_parent, 0);
	/* if error */

	srand(getpid());

	for (i = 0; i < 10; i++) {
		sem_wait(self);
		sleep((unsigned)rand() % 5 + 1);
		printf("%d ", ind);
		fflush(stdout);
		sem_post(parent);
	}
}

static int wait_all(sem_t *sem)
{
	int i = 0;
	int ret;

	while (i < PROC_NUM) {
		ret = sem_wait(sem);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			return -1;
		}

		i++;
	}
	return 0;
}

int main(void)
{
	pid_t pid;
	int i, j;
	sem_t *sem[PROC_NUM + 1];
	char name[PROC_NUM + 1][16];

	for (i = 0; i < PROC_NUM; i++) {
		snprintf(name[i], 16, "mysem%d", i);
		sem[i] = sem_open(name[i], O_CREAT, 0600, 1);
		/* if error */
	}
	snprintf(name[i], 16, "mysem%d", i);
	sem[i] = sem_open(name[i], O_CREAT, 0600, 0);
	/* if error */

	for (i = 0; i < PROC_NUM; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs(i);
			return 0;
		}
	}

	for (i = 0; i < 10; i++) {
		wait_all(sem[PROC_NUM]);
		printf("\n");
		for (j = 0; j < PROC_NUM; j++) {
			sem_post(sem[j]);
		}
	}

	for (i = 0; i < PROC_NUM; i++) {
		wait(NULL);
	}

	for (i = 0; i < PROC_NUM + 1; i++) {
		sem_close(sem[i]);
	}

	return 0;
}
