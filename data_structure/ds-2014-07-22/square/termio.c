#include <termios.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	int c;
	struct termios new, old;

	tcgetattr(0, &new);
	/* if error */
	tcgetattr(0, &old);
	/* if error */

	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);
	/* if error */

	while (1) {
		c = getchar();
		printf("%x %c ", c, c);
	}

	tcsetattr(0, TCSANOW, &old);
	/* if error */

	return 0;
}
