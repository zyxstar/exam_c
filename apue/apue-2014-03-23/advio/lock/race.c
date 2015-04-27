#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int lock(int fd)
{
	struct flock status;

	status.l_type = F_WRLCK;
	status.l_whence = SEEK_SET;
	status.l_start = 0;
	status.l_len = 0;

	return fcntl(fd, F_SETLKW, &status);
}

int unlock(int fd)
{
	struct flock status;

	status.l_type = F_UNLCK;
	status.l_whence = SEEK_SET;
	status.l_start = 0;
	status.l_len = 0;

	return fcntl(fd, F_SETLKW, &status);
}

int main(void)
{
	int value;
	char buf[BUFSIZE];
	FILE *fp;
	int i;
	int ret;
	int fd;

	fork();
	fork();

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("tmp");
		return 1;
	}

	fd = fileno(fp);

	for (i = 0; i < 1000; i++) {
		fseek(fp, 0, SEEK_SET);
		lock(fd);
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
		unlock(fd);
	}

	fclose(fp);

	return 0;
}
