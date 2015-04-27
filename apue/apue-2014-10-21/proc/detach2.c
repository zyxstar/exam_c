#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

void jobs(void)
{
	printf("in child, pid: %d\n", getpid());
}

int main(void)
{
	pid_t pid;
	int i;
	struct sigaction act;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

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
