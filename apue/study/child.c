#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <unistd.h>

static void	sig_cld(int);

int
main()
{
	pid_t	pid;

	if (signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) {		/* child */
		sleep(10);
		_exit(0);
	}

	pause();	/* parent */
	exit(0);
}

static void
sig_cld(int signo)	/* interrupts pause() */
{
	pid_t	pid;
	int		status;

	printf("SIGCLD received\n");

	if ((pid = wait(&status)) < 0)		/* fetch child status */
		perror("wait error");

	if (signal(SIGCLD, sig_cld) == SIG_ERR)	/* reestablish handler */
		perror("signal error");

	printf("pid = %d\n", pid);
}
