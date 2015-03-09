#include <time.h>

#include <stdio.h>

#define STRSIZE   64

int main(void)
{
	time_t cur;
	struct tm *cur_tm;
	char str[STRSIZE];

	cur = time(NULL);
	printf("cur = %d\n", cur);

	cur_tm = gmtime(&cur);
	printf("%d %d %d %d %d %d\n", cur_tm->tm_year, cur_tm->tm_mon, cur_tm->tm_mday, cur_tm->tm_hour, cur_tm->tm_min, cur_tm->tm_sec);

	cur_tm = localtime(&cur);
	printf("%d %d %d %d %d %d\n", cur_tm->tm_year, cur_tm->tm_mon, cur_tm->tm_mday, cur_tm->tm_hour, cur_tm->tm_min, cur_tm->tm_sec);

	strftime(str, STRSIZE, "xxxxx: %F %T", cur_tm);
	printf("%s\n", str);

	return 0;
}
