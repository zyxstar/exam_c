#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 32

static void my_rcv(void)
{
	FILE *fp0;
	char buf[BUFSIZE];
	char *retp;

	fp0 = fopen("fb0", "r");
	/* if error */

	while (1) {
		retp = fgets(buf, BUFSIZE, fp0);
		if (retp == NULL) {
			break;
		}
		printf("\033[31m");
		printf("%s", buf);
		printf("\033[0m");
		fflush(stdout);
	}

	fclose(fp0);
}

int main(void)
{
	FILE *fp1;
	pid_t pid;
	char buf[BUFSIZE];
	char *retp;

	pid = fork();
	/* if error */

	if (pid == 0) {
		my_rcv();
		exit(0);
	}

	fp1 = fopen("fb1", "w");
	/* if error */

	while (1) {
		retp = fgets(buf, BUFSIZE, stdin);
		if (retp == NULL) {
			break;
		}

		fprintf(fp1, "%s", buf);
		fflush(fp1);
	}

	fclose(fp1);
	kill(pid, 9);

	return 0;
}
