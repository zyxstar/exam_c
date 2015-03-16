#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	FILE *fp;
	int val;
	char buf[BUFSIZE];
	int i;
	pid_t pid;

	pid = fork();
	/* if error */

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("fopen(tmp)");
		return 1;
	}

	for (i = 0; i < 1000; i++) {
		fseek(fp, 0, SEEK_SET);
		fgets(buf, BUFSIZE, fp);
		val = atoi(buf);
		val++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", val);
	}

	fclose(fp);

	if (pid != 0) {
		wait(NULL);
	}

	return 0;
}
