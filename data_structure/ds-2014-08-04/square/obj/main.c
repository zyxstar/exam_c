#include <termios.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#include "fb_draw.h"
#include "comm.h"
#include "glob.h"
#include "display.h"
#include "move.h"

static void handle(int unuse)
{
	int ret;

	alarm(1);

	ret = move_down();
	if (ret == 0) {
		return;
	}

	little2big(main_arr);

	clear_line();

	init_little();
	display();
}

int main(void)
{
	int ret;
	struct termios new, old;
	int quit = 0;
	int input;

	srand(getpid());

	tcgetattr(0, &new);
	/* if error */
	tcgetattr(0, &old);
	/* if error */

	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);
	/* if error */

	ret = fb_open();
	if (ret) {
		perror("fb_open()");
		return 1;
	}

	signal(SIGALRM, handle);
	alarm(1);

	init();

	display();
	while (!quit) {
		input = getchar();
		switch (input) {
		case 'a':
			move_left();
			break;
		case 's':
			move_down();
			break;
		case 'd':
			move_right();
			break;
		case ' ':
			roll();
			break;
		case 'q':
			quit = 1;
			break;
		}
	}

	fb_close();

	tcsetattr(0, TCSANOW, &old);
	/* if error */

	return 0;
}
