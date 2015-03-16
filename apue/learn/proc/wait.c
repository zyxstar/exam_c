#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int status;

	pid = fork();
	/* if error */
	if (pid == 0) {
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
		//sleep(20);
		//printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
		return 0x45;
	}

	sleep(1);
	//wait(&status);
	//waitpid(-1, &status, 0);
	pid = waitpid(-1, &status, WNOHANG);
	printf("waitpid() return, pid = %d\n", pid);
	printf("status = %x\n", status);
	printf("status = %x\n", WEXITSTATUS(status));

	return 0;
}
