#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int shmid;
	char *ptr;
	pid_t pid;

	shmid = shmget(IPC_PRIVATE, 4096, 0600);
	/* if error */

	ptr = shmat(shmid, NULL, 0);

	pid = fork();
	/* if error */
	if (pid == 0) {
		snprintf(ptr, 4096, "hello shm\n");

		shmdt(ptr);
		exit(0);
	}

	sleep(1);
	printf("%s", ptr);

	shmdt(ptr);
	wait(NULL);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
