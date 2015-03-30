#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	int shmid;
	pid_t pid;
	char *ptr;

	shmid = shmget(IPC_PRIVATE, 4096, 0666);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		ptr = shmat(shmid, NULL, 0);
		/* if error */

		snprintf(ptr, 4096, "hello share memory.");

		shmdt(ptr);
		return 0;
	}

	ptr = shmat(shmid, NULL, SHM_RDONLY);
	/* if error */

	sleep(1);
	printf("%s\n", ptr);

	shmdt(ptr);

	wait(NULL);

	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
