#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	int a, b, c;
	int (*funcp)(int, int);
	char *ptr;
	int fd;

	fd = open("add.plugin", O_RDONLY);
	if (fd == -1) {
		perror("open(add.plugin)");
		return 1;
	}

	ptr = mmap(NULL, 4096, PROT_EXEC | PROT_READ, MAP_PRIVATE, fd, 0);
	/* if error */
	funcp = (void *)(ptr + 0x3e0);

	a = 123, b = 456;
	c = funcp(a, b);

	printf("c = %d\n", c);

	close(fd);

	return 0;
}
