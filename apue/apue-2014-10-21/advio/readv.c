#include <sys/uio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF1SIZE 11
#define BUF2SIZE 12
#define BUF3SIZE 13

int main(void)
{
	int fd;
	int ret;
	char buf1[BUF1SIZE];
	char buf2[BUF2SIZE];
	char buf3[BUF3SIZE];
	struct iovec vec[3] = {
		{buf1, BUF1SIZE},
		{buf2, BUF2SIZE},
		{buf3, BUF3SIZE},
};

	fd = open("ff", O_RDONLY);
	/* if error */

	ret = readv(fd, vec, 3);

	write(1, "\033[31m", 5);
	if (ret < BUF1SIZE) {
		write(1, buf1, ret);
	} else {
		write(1, buf1, BUF1SIZE);
	}
	ret -= BUF1SIZE;
	if (ret > 0 && ret < BUF2SIZE) {
		write(1, "\033[32m", 5);
                write(1, buf2, ret);
        } else {
		write(1, "\033[32m", 5);
                write(1, buf2, BUF2SIZE);
        }
	ret -= BUF2SIZE;
        if (ret > 0) {
		write(1, "\033[33m", 5);
                write(1, buf3, ret);
        }
	write(1, "\033[0m", 4);

	close(fd);

	return 0;
}
