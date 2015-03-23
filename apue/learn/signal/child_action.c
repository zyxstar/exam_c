#include <signal.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	int i;
	pid_t pid;
	struct sigaction act;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	for (i = 0; i < 6; i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			return 0;
		}
	}

	while (1) {
		pause();
	}

	return 0;
}
