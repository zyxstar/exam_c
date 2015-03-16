#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

/* ./mykill signo pid */
int main(int argc, char **argv)
{
	int signo;
	pid_t pid;

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	signo = atoi(argv[1]);
	pid = atoi(argv[2]);

	kill(pid, signo);

	return 0;
}
