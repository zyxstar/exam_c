#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

void handler(int unuse)
{
	printf("call handler()\n");
}

int main(void)
{
	char buf[BUFSIZE];
	int ret;
	struct itimerval ival = {
		{2, 0},
		{6, 0},
	};

	signal(SIGALRM, handler);

	setitimer(ITIMER_REAL, &ival, NULL);

	while (1) {
		printf("will call read()\n");
		read(0, buf, BUFSIZE);
		printf("read() return\n");
	}

	return 0;
}
