#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdio.h>

#define N         100000
#define PROC_NR   9
#define BUFSIZE   64

static int semid;

static int lock(void)
{
	struct sembuf opbuf;

	opbuf.sem_num = 0;
	opbuf.sem_op  = -1;
	opbuf.sem_flg = SEM_UNDO;
	return semop(semid, &opbuf, 1 /* array num */);
}

static int unlock(void)
{
	struct sembuf opbuf;

	opbuf.sem_num = 0;
	opbuf.sem_op  = 1;
	opbuf.sem_flg = SEM_UNDO;
	return semop(semid, &opbuf, 1 /* array num */);
}

void jobs(void)
{
	FILE *fp;
	char buf[BUFSIZE];
	int val;
	int i;

	fp = fopen("tmp", "r+");
	/* if error */

	for (i = 0; i < N; i++) {
		fseek(fp, 0, SEEK_SET);
		lock();
		fgets(buf, BUFSIZE, fp);
		val = atoi(buf);
		val++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", val);
		fflush(fp);
		unlock();
	}

	fclose(fp);
}

int main(void)
{
	int i;
	pid_t pid;

	semid = semget(IPC_PRIVATE, 1, 0600);
	/* if error */

	semctl(semid, 0, SETVAL, 1);
	/* if error */

	for (i = 0; i < PROC_NR; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs();
			return 0;
		}
	}

	for (i = 0; i < 6; i++) {
		wait(NULL);
	}

	semctl(semid, -1, IPC_RMID);

	return 0;
}
