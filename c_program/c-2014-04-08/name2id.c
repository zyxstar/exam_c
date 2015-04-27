#include <stdio.h>

#define BUFSIZE 1024

int get_info(char *str, char **name, int *uid)
{
	char *n, *u;

	n = str;
	for (; *str != ':'; str++)
		;
	*str = '\0';

	for (str++; *str != ':'; str++)
                ;
	u = str + 1;

	*name = n;
	*uid = atoi(u);

	return 0;
}

/* $ ./a.out name */
int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;
	char *name;
	int uid;
	int eof;
	int i;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen("/etc/passwd", "r");
	if (fp == NULL) {
		printf("fopen() failed\n");
		return 1;
	}

	eof = 0;
	while (eof == 0) {
#if 0
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}
#else
		for (i = 0; ; i++) {
			buf[i] = fgetc(fp);
			if (buf[i] == EOF) {
				eof = 1;
			}
			if (buf[i] == '\n' || buf[i] == EOF) {
				buf[i] = '\0';
				break;
			}
		}
#endif

		get_info(buf, &name, &uid);
		if (strcmp(name, argv[1]) == 0) {
			printf("uid: %d\n", uid);
			fclose(fp);
			return 0;
		}
	}

	printf("Can not find.\n");
	fclose(fp);

	return 0;
}
