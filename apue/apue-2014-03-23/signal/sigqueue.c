#include <sys/types.h>
#include <signal.h>

#include <stdio.h>

/* $./a.out pid signo value */
int main(int argc, char **argv)
{
	pid_t pid;
	int signo;
	union sigval value;
	int ret;

	if (argc != 4) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	pid = atoi(argv[1]);
	signo = atoi(argv[2]);
	value.sival_int = atoi(argv[3]);

	printf("pid = %d\n", getpid());

	ret = sigqueue(pid, signo, value);
	if (ret == -1) {
		perror(argv[1]);
	}

	return 0;
}
