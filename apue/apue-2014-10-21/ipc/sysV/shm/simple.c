#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include <stdio.h>

#define PAGESIZE 4096

int main(void)
{
	pid_t pid;
	int shmid;
	void *ptr;

	shmid = shmget(IPC_PRIVATE, PAGESIZE, 0666);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);

		snprintf(ptr, PAGESIZE, "hello share memory");

		shmdt(ptr);
		return 0;
	}

	ptr = shmat(shmid, NULL, SHM_RDONLY);

	sleep(1);
	printf("%s\n", ptr);

	shmdt(ptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
