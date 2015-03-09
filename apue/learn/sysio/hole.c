#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("./tmp", O_WRONLY | O_CREAT, 0644);
	/* if error */

	lseek(fd, 1024 * 1024 * 1024, SEEK_SET);
	write(fd, "xxx", 3);

	close(fd);

	return 0;
}
