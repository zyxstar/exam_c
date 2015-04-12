#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int fd;
	char *ptr;
	char *s;

	fd = open("hello.c", O_RDWR);
	/* if error */

	ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	/* if error */

	printf("%s", ptr);
	s = strstr(ptr, "return");
	strncpy(s, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 32);
	printf("%s\n", ptr);

	msync(ptr, 4096, MS_SYNC);

	munmap(ptr, 4096);

	close(fd);

	return 0;
}
