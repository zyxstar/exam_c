#include <stdio.h>

int main(void)
{
	char buf[256] = "abcdefg_XXXXXX";
	int fd;

	//tmpnam(buf);
	fd = mkstemp(buf);
	printf("%s\n", buf);

	sleep(60);

	close(fd);

	return 0;
}
