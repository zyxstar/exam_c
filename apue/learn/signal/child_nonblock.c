#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

void handler(int unuse)
{
	pid_t pid;

	while (1) {
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid == 0 || pid == -1) {
			break;
		}
	}
}

int main(void)
{
	int i;
	pid_t pid;

	signal(SIGCHLD, handler);

	for (i = 0; i < 6; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			return 0;
		}
	}

	while (1) {
		sleep(2);
		printf("xxx\n");
	}

	return 0;
}
