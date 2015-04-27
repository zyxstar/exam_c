#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	int fd;
	char *ptr;

	fd = open("passwd", O_RDWR);
	/* if error */

	ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	/* if error */

	write(1, ptr, 100);

	/* fix me */
	printf("\n");
	fflush(stdout);

	strncpy(ptr, "OOOO", 4);
	write(1, ptr, 100);

	munmap(ptr, 4096);

	close(fd);

	return 0;
}
