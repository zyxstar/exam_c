#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <stdio.h>

#define PROC_NUM   6

static int dec(int semid, int ind)
{
	struct sembuf buf;

	buf.sem_num = ind;
	buf.sem_op = -1;
	buf.sem_flg = 0;

	return semop(semid, &buf, 1);
}

static int inc(int semid, int ind)
{
	struct sembuf buf;

	buf.sem_num = ind;
	buf.sem_op = 1;
	buf.sem_flg = 0;

	return semop(semid, &buf, 1);
}

static void jobs(int semid, int ind)
{
	int i;

	srand(getpid());

	for (i = 0; i < 10; i++) {
		dec(semid, ind);
		sleep((unsigned)rand() % 5 + 1);
		printf("%d ", ind);
		fflush(stdout);
		inc(semid, PROC_NUM);
	}
}

static int wait_all(int semid)
{
	struct sembuf buf;

	buf.sem_num = PROC_NUM;
	buf.sem_op = -PROC_NUM;
	buf.sem_flg = 0;

	return semop(semid, &buf, 1);
}

int main(void)
{
	pid_t pid;
	int i;
	int semid;
	unsigned short init_arr[PROC_NUM + 1];
	struct sembuf buf[PROC_NUM];

	semid = semget(IPC_PRIVATE, PROC_NUM + 1, 0600);
	/* if error */

	for (i = 0; i < PROC_NUM; i++) {
		init_arr[i] = 1;
	}
	init_arr[i] = 0;
	semctl(semid, -1, SETALL, init_arr);

	for (i = 0; i < PROC_NUM; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs(semid, i);
			return 0;
		}
	}

	/* init op_arr */
	for (i = 0; i < PROC_NUM; i++) {
		buf[i].sem_num = i;
		buf[i].sem_op = 1;
		buf[i].sem_flg = 0;
	}

	for (i = 0; i < 10; i++) {
		wait_all(semid);
		printf("\n");
		semop(semid, buf, PROC_NUM);
	}

	for (i = 0; i < PROC_NUM; i++) {
		wait(NULL);
	}

	return 0;
}
