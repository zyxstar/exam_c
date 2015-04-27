#include <signal.h>
#include <termios.h>
#include <unistd.h>

#include <stdio.h>

void handler(int unuse)
{
	alarm(2);
	printf("Catch signal.\n");
}

int main(void)
{
	int i;
	struct termios attr;
	int c;

	tcgetattr(0, &attr);

	attr.c_lflag &= ~ICANON;
	attr.c_lflag &= ~ECHO;
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &attr);

	signal(SIGALRM, handler);
	alarm(3);

	while (1) {
		c = getchar();
		printf("%x ", c);
		fflush(NULL);
	}

	return 0;
}
