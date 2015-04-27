#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include <stdio.h>

#define PAGESIZE 4096

int main(void)
{
	pid_t pid;
	int shmid;
	void *ptr;
	int semid;
	struct sembuf opbuf;

	semid = semget(IPC_PRIVATE, 1, 0666);
	/* if error */

	semctl(semid, 0, SETVAL, 0);

	shmid = shmget(IPC_PRIVATE, PAGESIZE, 0666);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);

		snprintf(ptr, PAGESIZE, "hello share memory");
		opbuf.sem_num = 0;
		opbuf.sem_op = 1;
		opbuf.sem_flg = 0;
		semop(semid, &opbuf, 1);

		shmdt(ptr);
		return 0;
	}

	ptr = shmat(shmid, NULL, SHM_RDONLY);

	opbuf.sem_num = 0;
	opbuf.sem_op = -1;
	opbuf.sem_flg = 0;
	semop(semid, &opbuf, 1);
	printf("%s\n", ptr);

	shmdt(ptr);
	shmctl(shmid, IPC_RMID, NULL);

	semctl(semid, -1, IPC_RMID);

	return 0;
}
