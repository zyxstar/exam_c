#include <stdio.h>

#define BUFSIZE 32

/* ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	char c;
	char buf[BUFSIZE];
	char *retp;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("%s error.\n", argv[1]);
		return 1;
	}

	while (1) {
#if 0
		c = fgetc(fp);
		if (c == EOF) {
			break;
		}
		printf("%c", c);
#else
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}
		printf("%s", buf);
#endif
	}

	fclose(fp);

	return 0;
}
