#include <stdio.h>
#include <errno.h>

#define BUFSIZE   40

/* ./a.out filename */
int main(int argc, char **argv)
{
	FILE *fp;
	char c;
	char buf[BUFSIZE];
	char *retp;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		//fprintf(stderr, "fopen(%s) failed, errno = %d\n", argv[1], errno);
		perror(argv[1]);
		return 1;
	}

	while (1) {
#if 0
		c = fgetc(fp);
		if (c == EOF) {
			break;
		}
		putchar(c);
#else
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}

		//printf("%s", buf);
		fprintf(stdout, "%s", buf);
#endif
	}

	fclose(fp);

	return 0;
}
