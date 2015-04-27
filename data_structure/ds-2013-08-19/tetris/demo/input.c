#include <termios.h>
#include <unistd.h>

#include <stdio.h>

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

	while (1) {
		c = getchar();
		printf(" %x\n", c);
	}

	return 0;
}
