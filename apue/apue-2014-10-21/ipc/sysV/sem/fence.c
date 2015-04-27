#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <stdio.h>

#define PROC_NR    9
#define TIMES      12

static int sub(int semid, int ind, int val)
{
	struct sembuf opbuf;

	opbuf.sem_num = ind;
	opbuf.sem_op = -val;
	opbuf.sem_flg = 0;

	return semop(semid, &opbuf, 1);
}

static int add(int semid, int ind, int val)
{
	struct sembuf opbuf;

	opbuf.sem_num = ind;
	opbuf.sem_op = val;
	opbuf.sem_flg = 0;

	return semop(semid, &opbuf, 1);
}

static int inc(int semid, int ind)
{
	return add(semid, ind, 1);
}

static int dec(int semid, int ind)
{
	return sub(semid, ind, 1);
}

static void jobs(int ind, int semid)
{
	int i;

	srand(getpid());

	for (i = 0; i < TIMES; i++) {
		dec(semid, ind);
		sleep((unsigned)rand() % 4 + 1);
		printf("%d ", ind);
		fflush(stdout);
		inc(semid, PROC_NR);
	}

}

int main(void)
{
	pid_t pid;
	int i;
	int semid;
	unsigned short init_arr[PROC_NR + 1] = {[PROC_NR] = PROC_NR};
	struct sembuf oparr[PROC_NR];

	semid = semget(IPC_PRIVATE, PROC_NR + 1, 0600);
	/* if error */

	/* init */
	semctl(semid, -1, SETALL, init_arr);

	for (i = 0; i < PROC_NR; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs(i, semid);
			return 0;
		}
	}

	for (i = 0; i < PROC_NR; i++) {
		oparr[i].sem_num = i;
		oparr[i].sem_op = 1;
		oparr[i].sem_flg = 0;
	}

	for (i = 0; i < TIMES; i++) {
		sub(semid, 
		    PROC_NR /* ind */,
		    PROC_NR /* val */);

		printf("\n");
		fflush(stdout);

		semop(semid, oparr, PROC_NR);
	}

	for (i = 0; i < PROC_NR; i++) {
		wait(NULL);
	}

	semctl(semid, -1, IPC_RMID);

	return 0;
}
