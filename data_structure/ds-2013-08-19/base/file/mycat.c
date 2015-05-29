#include <stdio.h>

/* $ ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	char c;

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
		c = fgetc(fp);
		if (c == EOF) {
			break;
		}

		printf("%c", c);
	}

	fclose(fp);

	return 0;
}