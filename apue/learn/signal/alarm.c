#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

void handler(int unuse)
{
	alarm(4);
	printf("call handler()\n");
}

int main(void)
{
	char buf[BUFSIZE];
	int ret;

	signal(SIGALRM, handler);

	alarm(20);
	sleep(3);
	ret = alarm(30);
	printf("ret = %d\n", ret);

	while (1) {
		printf("will call read()\n");
		read(0, buf, BUFSIZE);
		printf("read() return\n");
	}

	return 0;
}
