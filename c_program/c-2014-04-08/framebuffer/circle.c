#include "fb_draw.h"

static int x, y, r, dir, color;

void init(void)
{
	srand(getpid());

	x = (unsigned)rand() % (xres() - 200) + 100;
	y = (unsigned)rand() % (yres() - 200) + 100;
	dir = (unsigned)rand() % 4;
	r = 50;
	color = 0xaf;
}

void circle(int x, int y, int r, int color)
{
	int i, j;

	for (i = x - r; i <= x + r; i++) {
		for (j = y - r; j <= y + r; j++) {
			if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
				fb_draw_point(i, j, color);
			}
		}
	}
}

void move(void)
{
	circle(x, y, r, 0);

	switch (dir) {
	case 0:
		x++; y--;
		break;
	case 1:
		x++; y++;
		break;
	case 2:
		x--; y++;
		break;
	case 3:
		x--; y--;
		break;
	}
	circle(x, y, r, color);
}

void change_dir(void)
{
	if (x - r == 0 && y - r == 0) {
		dir = 1;
	} else if (x - r == 0 && y + r == yres() - 1) {
		dir = 0;
	} else if (x + r == xres() - 1 && y - r == 0) {
		dir = 2;
	} else if (x + r == xres() - 1 && y + r == yres() - 1) {
		dir = 3;
	} else if (x - r == 0) {
		if (dir == 2) {
			dir = 1;
		} else {
			dir = 0;
		}
	} else if (x + r == xres() - 1) {
		if (dir == 0) {
			dir = 3;
		} else {
			dir = 2;
		}
	} else if (y - r == 0) {
		if (dir == 0) {
			dir = 1;
		} else {
			dir = 2;
		}
	} else if (y + r == yres() - 1) {
		if (dir == 1) {
			dir = 0;
		} else {
			dir = 3;
		}
	}
}

int main(void)
{
	int ret;

	ret = fb_open();
	if (ret != 0) {
		fprintf(stderr, "fb_open() error.\n");
		exit(1);
	}

	init();

	while (1) {
		move();
		change_dir();
		usleep(30000);
	}

	fb_close();

	return 0;
}
