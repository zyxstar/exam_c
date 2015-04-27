#include <stdio.h>
#include <errno.h>

#define BUFSIZE   40

/* ./a.out filename */
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
		perror(argv[1]);
		return 1;
	}

	fseek(fp, 20, SEEK_SET);

	while (1) {
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}

		fprintf(stdout, "%s", buf);
	}

	fclose(fp);

	return 0;
}
