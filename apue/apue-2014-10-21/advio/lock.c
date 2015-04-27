#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE 32
#define PROC_NR 16

static int lock(int fd)
{
	struct flock lock_buf;

	lock_buf.l_type = F_WRLCK;
	lock_buf.l_whence = SEEK_SET;
	lock_buf.l_start = 0;
	lock_buf.l_len = 0;
	return fcntl(fd, F_SETLKW, &lock_buf);
}

static int unlock(int fd)
{
	struct flock lock_buf;

	lock_buf.l_type = F_UNLCK;
	lock_buf.l_whence = SEEK_SET;
	lock_buf.l_start = 0;
	lock_buf.l_len = 0;
	return fcntl(fd, F_SETLKW, &lock_buf);
}

int main(void)
{
	FILE *fp;
	int fd;
	pid_t pid;
	char buf[BUFSIZE];
	int i;
	int val;
	int ret;

	fp = fopen("tmp", "r+");
	/* if error */
	fd = fileno(fp);

	for (i = 0; i < PROC_NR; i++) {
		pid = fork();
		/* if error */
		/* fix me */
		if (pid == 0) {
			break;
		}
	}

	i = 0;
	while (i < 10000) {
		ret = lock(fd);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("lock()");
			break;
		}

		fseek(fp, 0, SEEK_SET);
		fgets(buf, BUFSIZE, fp);
		val = atoi(buf);
		val++;
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n", val);
		fflush(fp);
		unlock(fd);

		i++;
	}

	fclose(fp);

	if (pid) {
		for (i = 0; i < PROC_NR; i++) {
			wait(NULL);
		}
	}

	return 0;
}
