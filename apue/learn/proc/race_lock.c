#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#define BUFSIZE 128

static int lock(int fd)
{
	struct flock lock;

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	return fcntl(fd, F_SETLKW, &lock);
}

static int unlock(int fd)
{
	struct flock lock;

	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	return fcntl(fd, F_SETLKW, &lock);
}

int main(void)
{
	FILE *fp;
	int val;
	char buf[BUFSIZE];
	int i;
	pid_t pid;
	int fd;

	pid = fork();
	/* if error */

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("fopen(tmp)");
		return 1;
	}

	fd = fileno(fp);

	for (i = 0; i < 1000; i++) {
		lock(fd);
		fseek(fp, 0, SEEK_SET);
		fgets(buf, BUFSIZE, fp);
		val = atoi(buf);
		val++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", val);
		fflush(fp);
		unlock(fd);
	}

	fclose(fp);

	if (pid != 0) {
		wait(NULL);
	}

	return 0;
}
