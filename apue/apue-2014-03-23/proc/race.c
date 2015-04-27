#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(void)
{
	int value;
	char buf[BUFSIZE];
	FILE *fp;
	int i;
	int ret;

	fork();
	fork();

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("tmp");
		return 1;
	}

	for (i = 0; i < 1000; i++) {
		usleep(100000);
		fseek(fp, 0, SEEK_SET);
		ret = fread(buf, 1, BUFSIZE, fp);
		if (ret == 0) {
			//perror("fread()");
			break;
		}
		buf[ret] = '\0';
		value = atoi(buf);
		value++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", value);
		fflush(fp);
	}

	fclose(fp);

	return 0;
}
