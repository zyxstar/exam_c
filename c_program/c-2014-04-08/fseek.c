#include <stdio.h>

#define BUFSIZE 1024

/* $ ./a.out filename */
int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("fopen() failed\n");
		return 1;
	}

	fseek(fp, 20, SEEK_SET);

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
