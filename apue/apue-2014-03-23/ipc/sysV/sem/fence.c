#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define PROC_NR 5
#define TIMES   10

static int semid;

static void sub(int ind, int n)
{
	struct sembuf opbuf;

	opbuf.sem_num = ind;
	opbuf.sem_op = -n;
	opbuf.sem_flg = 0;
	semop(semid, &opbuf, 1);
}

static void add(int ind, int n)
{
        struct sembuf opbuf;

        opbuf.sem_num = ind;
	opbuf.sem_op = n;
        opbuf.sem_flg = 0;
        semop(semid, &opbuf, 1);
}

void dec(int ind)
{
	sub(ind, 1);
}

void inc(int ind)
{
	add(ind, 1);
}

void job(int ind)
{
	int i;
	int sec;

	srand(getpid());

	for (i = 0; i < TIMES; i++) {
		dec(ind);
		sec = (unsigned)rand() % 5;
		sleep(sec);
		printf("%d ", ind);
		fflush(NULL);
		inc(PROC_NR);
	}
}

static void main_inc(void)
{
        struct sembuf opbuf[PROC_NR];
	int i;

	for (i = 0; i < PROC_NR; i++) {
		opbuf[i].sem_num = i;
		opbuf[i].sem_op = 1;
		opbuf[i].sem_flg = 0;
	}
        semop(semid, opbuf, PROC_NR);
}

int main(void)
{
	pid_t pid;
	int i;
	unsigned short set_all_val[PROC_NR + 1] = {};

	for (i = 0; i < PROC_NR; i++) {
		set_all_val[i] = 1;
	}

	semid = semget(IPC_PRIVATE, PROC_NR + 1, 0600);
	/* if error */

	semctl(semid, 0, SETALL, set_all_val);

	for (i = 0; i < PROC_NR; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			job(i);
			exit(0);
		}
	}

	for (i = 0; i < TIMES; i++) {
		sub(PROC_NR, PROC_NR);
		printf("\n");
		fflush(NULL);
#if 0
		semctl(semid, 0, SETALL, set_all_val);
#else
		main_inc();
#endif
	}

	for (i = 0; i < PROC_NR; i++) {
		wait(NULL);
	}

	semctl(semid, 0, IPC_RMID, 0);

	return 0;
}
