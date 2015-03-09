#include <stdlib.h>
#include <stdio.h>

#define NAMESIZE  64

int main(void)
{
	int fd;
	char name[NAMESIZE] = "./abcdXXXXXX";

	fd = mkstemp(name);
	/* if error */

	printf("%s\n", name);

	write(fd, "hello tmp\n", 10);

	close(fd);

	return 0;
}
