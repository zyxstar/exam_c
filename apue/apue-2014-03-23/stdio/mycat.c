#include <stdio.h>

#define BUFSIZE 32

/* $ ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	int ret;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen() err.\n");
		return 1;
	}

	while (1) {
		ret = fread(buf, 1, BUFSIZE, fp);
		if (ret == 0) {
			break;
		}

		fwrite(buf, 1, ret, stdout);
	}

	fclose(fp);

	return 0;
}
