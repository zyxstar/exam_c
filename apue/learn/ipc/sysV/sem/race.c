#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

static int lock(int semid)
{
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;

	return semop(semid, &buf, 1);
}

static int unlock(int semid)
{
	struct sembuf buf;

	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;

	return semop(semid, &buf, 1);
}

int main(void)
{
	FILE *fp;
	int val;
	char buf[BUFSIZE];
	int i;
	pid_t pid;
	int semid;

	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
	/* if error */

	semctl(semid, 0, SETVAL, 1);

	pid = fork();
	/* if error */

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("fopen(tmp)");
		return 1;
	}

	for (i = 0; i < 1000; i++) {
		lock(semid);
		fseek(fp, 0, SEEK_SET);
		fgets(buf, BUFSIZE, fp);
		val = atoi(buf);
		val++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", val);
		fflush(fp);
		unlock(semid);
	}

	fclose(fp);

	if (pid != 0) {
		wait(NULL);
		semctl(semid, -1, IPC_RMID);
	}

	return 0;
}
