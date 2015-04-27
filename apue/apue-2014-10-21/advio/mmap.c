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
	struct stat status;
	int len;
	int ret;

	fd = open("tmp", O_RDWR);
	if (fd == -1) {
		perror("open(tmp)");
		return 1;
	}

	ret = stat("tmp", &status);
	/* if error */
	len = status.st_size;

	ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == (void *)-1) {
		perror("mmap()");
		close(fd);
		return 1;
	}

	ptr[len] = '\0';
	printf("%s\n", ptr);
	strncpy(ptr + 6, "yyyyyyyy", 5);

	msync(ptr, 4096, MS_SYNC);

	munmap(ptr, 4096);

	close(fd);

	return 0;
}
