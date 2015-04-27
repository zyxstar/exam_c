#include <termios.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	int c;
	struct termios attr;

	tcgetattr(0, &attr);

	attr.c_lflag &= ~ICANON;
	attr.c_lflag &= ~ECHO;
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &attr);

	while (1) {
		c = getchar();
		printf("%x ", c);
		fflush(NULL);
	}

	return 0;
}
