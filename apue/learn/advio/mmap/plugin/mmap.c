#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd;
	char *ptr;
	int (*funcp)(int, int);

	fd = open("add.plugin", O_RDONLY);
	if (fd == -1) {
		perror("add.plugin");
		return 1;
	}

	ptr = mmap(NULL, 4096, PROT_EXEC | PROT_READ, MAP_PRIVATE, fd, 0);
	/* if error */

	/* cal offset by yourself */
	funcp = (void *)(ptr + 0x3e0);
	printf("%d\n", funcp(33, 66));

	munmap(ptr, 4096);

	close(fd);

	return 0;
}
