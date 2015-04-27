#include <sys/types.h>
#include <signal.h>

#include <stdio.h>

/* $./a.out pid signo */
int main(int argc, char **argv)
{
	pid_t pid;
	int signo;
	int ret;

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	pid = atoi(argv[1]);
	signo = atoi(argv[2]);

	ret = kill(pid, signo);
	if (ret == -1) {
		perror(argv[1]);
	}

	return 0;
}
