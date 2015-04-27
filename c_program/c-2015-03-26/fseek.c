#include <stdio.h>

#define BUFSIZE 32

/* ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	char c;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("%s error.\n", argv[1]);
		return 1;
	}

	fseek(fp, 9, SEEK_SET);
	/* if error */

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
