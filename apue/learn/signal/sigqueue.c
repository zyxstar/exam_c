#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

/* ./mykill signo pid val */
int main(int argc, char **argv)
{
	int signo;
	pid_t pid;
	union sigval val;

	if (argc != 4) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	signo = atoi(argv[1]);
	pid = atoi(argv[2]);
	val.sival_int = atoi(argv[3]);

	sigqueue(pid, signo, val);

	return 0;
}
