#include <sys/time.h>

#include <stdio.h>

void my_sleep(int sec)
{
	struct timeval val;

	val.tv_sec = sec;
	val.tv_usec = 0;
	select(0, NULL, NULL, NULL, &val);
}

int main(void)
{
	int i;

	for (i = 0; ; i++) {
		my_sleep(2);
		printf("i = %d\n", i);
	}

	return 0;
}
