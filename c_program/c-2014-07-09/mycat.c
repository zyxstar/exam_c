#include <stdio.h>

/* $ ./a.out pathname */
int main(int argc, char **argv)
{
	FILE *fp;
	int c;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("fopen(%s) failed\n", argv[1]);
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
