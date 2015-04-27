#include <termios.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	int c;
	struct termios attr, old;

	tcgetattr(0, &old);
	tcgetattr(0, &attr);
	/* if error */
	//old = attr;

	attr.c_lflag &= ~(ICANON | ECHO);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &attr);

	while (1) {
		c = getchar();
		if (c == 'q') {
			break;
		}
		printf("%x\n", c);
	}

	tcsetattr(0, TCSANOW, &old);

	return 0;
}
