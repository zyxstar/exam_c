#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

void jobs(void)
{
	printf("in child, pid: %d\n", getpid());
}

void mywait(int unuse)
{
	int ret;

	while (1) {
		ret = waitpid(-1, NULL, WNOHANG);
		if (ret == 0 || ret == -1) {
			break;
		}
	}
}

int main(void)
{
	pid_t pid;
	int i;

	signal(SIGCHLD, mywait);

	for (i = 0; i < 200; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs();
			return 0;
		}
	}

	while (1) {
		pause();
	}

	return 1;
}
