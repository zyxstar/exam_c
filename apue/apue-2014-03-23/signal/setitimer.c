#include <sys/time.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

void handler(int unuse)
{
	printf("%s\n", __func__);
}

int main(void)
{
	int i;
	struct itimerval value, ovalue;

	signal(SIGALRM, handler);

	value.it_value.tv_sec = 5;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 100000;
	setitimer(ITIMER_REAL, &value, &ovalue);

	while (1) {
		pause();
	}

	return 0;
}
