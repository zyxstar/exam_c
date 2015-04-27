#include <termios.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>

void handler(int unuse)
{
	alarm(1);
	printf(" Catch a signal\n");
}

int main(void)
{
	char c;

	struct termios status;
	int ret;

	ret = tcgetattr(0, &status);
	/* if error */

	status.c_lflag &= ~ICANON;
	status.c_lflag &= ~ECHO;

	status.c_cc[VMIN] = 1;
	status.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &status);

	signal(SIGALRM, handler);
	alarm(1);

	while (1) {
		c = getchar();
		printf("%x ", c);
		fflush(NULL);
	}

	return 0;
}
