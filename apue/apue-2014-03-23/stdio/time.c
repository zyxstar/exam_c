#include <time.h>

#include <stdio.h>

#define BUFSIZE 64

int main(void)
{
	time_t cur;
	struct tm *cur_tm;
	char buf[BUFSIZE];

	cur = time(NULL);
	printf("%ul\n", cur);

	cur_tm = localtime(&cur);
	strftime(buf, BUFSIZE, "%D - %T", cur_tm);
	printf("%s\n", buf);

	return 0;
}
