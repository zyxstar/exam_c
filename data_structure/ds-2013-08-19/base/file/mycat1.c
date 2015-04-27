#include <stdio.h>

#define BUFSIZE 32

/* $ ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen() failed.\n");
		return 1;
	}

	while (1) {
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}

		printf("%s", buf);
	}

	fclose(fp);

	return 0;
}
