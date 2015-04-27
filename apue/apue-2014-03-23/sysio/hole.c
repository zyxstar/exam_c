#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;

	fd = open("./tmp", O_WRONLY);
	/* if error */

	lseek(fd, 1024 * 1024 * 1024, SEEK_SET);
	write(fd, "hello", 5);

	close(fd);

	return 0;
}
