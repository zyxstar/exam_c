#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void wait_handler(int unuse)
{
	pid_t ret;

	while (1) {
		ret = waitpid(-1, NULL, WNOHANG);
		if (ret == 0) {
			break;
		}
		if (ret == -1 && errno == ECHILD) {
			break;
		}
	}
}

int main(void)
{
	pid_t pid;
	int i;
	int sec;

	signal(SIGCHLD, wait_handler);

	for (i = 0; i < 20; i++) {
		sec = (unsigned)rand() % 60;
		pid = fork();
		/* if error */

		if (pid == 0) {
			sleep(sec);
			exit(0);
		}
	}

	for (i = 0; ; i++) {
		printf("i = %d\n", i);
		sleep(3);
	}

	return 0;
}
