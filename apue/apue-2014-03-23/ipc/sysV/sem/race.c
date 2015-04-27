#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define TIMES   10000
#define PROC_NR 16

#define BUFSIZE 256

static int semid;

void lock(void)
{
	struct sembuf opbuf;

	opbuf.sem_num = 0;
	opbuf.sem_op = -1;
	opbuf.sem_flg = SEM_UNDO;
	semop(semid, &opbuf, 1);
}

void unlock(void)
{
	struct sembuf opbuf;

	opbuf.sem_num = 0;
	opbuf.sem_op = 1;
	opbuf.sem_flg = SEM_UNDO;
	semop(semid, &opbuf, 1);
}

void job(void)
{
	int value;
	char buf[BUFSIZE];
	FILE *fp;
	int i;
	int ret;

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("tmp");
		return;
	}

	for (i = 0; i < TIMES; i++) {
		fseek(fp, 0, SEEK_SET);
		lock();
		ret = fread(buf, 1, BUFSIZE, fp);
		if (ret == 0) {
			perror("fread()");
			break;
		}
		buf[ret] = '\0';
		value = atoi(buf);
		value++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", value);
		fflush(fp);
		unlock();
	}

	fclose(fp);
}

int main(void)
{
	pid_t pid;
	int i;

	semid = semget(IPC_PRIVATE, 1, 0666);
	if (semid == -1) {
		perror("semget()");
		return 1;
	}

	semctl(semid, 0, SETVAL, 1);

	for (i = 0; i < PROC_NR; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			job();
			exit(0);
		}
	}

	for (i = 0; i < PROC_NR; i++) {
		wait(NULL);
	}

	semctl(semid, 0, IPC_RMID, 0);

	return 0;
}
