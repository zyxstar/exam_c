#include <stdio.h>

#include "fb_draw.h"

static int x, y;
static int r;
static int color;
static int dir;

static void init(void)
{
	srand(getpid());

	r = 50;
	x = (unsigned)rand() % (xres() - 200) + 100;
	y = (unsigned)rand() % (yres() - 200) +100;

	color = (unsigned)rand() % (0xff - 0x30) + 0x30;

	//dir = (unsigned)rand() % 4 + 1;
	dir = 3;
}

static void circle(int x, int y, int r, int color)
{
	int i, j;

	for (i = x - r; i < x + r + 1; i++) {
		for (j = y - r; j < y + r + 1; j++) {
			if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
				fb_draw_point(i, j, color);
			}
		}
	}
}

static void move(void)
{
	circle(x, y, r, 0);

	switch (dir) {
	case 1:
		if (x == (xres() - r - 1) && y == r) {
			dir = 3;
		} else if (x == (xres() - r - 1)) {
			dir = 4;
		} else if (y == r) {
			dir = 2;
		}
		break;
	case 2:
		if (x == (xres() - r - 1) && y == (yres() - r - 1)) {
			dir = 4;
		} else if (x == (xres() - r - 1)) {
			dir = 3;
		} else if (y == (yres() - r - 1)) {
			dir = 1;
		}
		break;
	case 3:
		if (x == r && y == (yres() - r - 1)) {
			dir = 1;
		} else if (x == r) {
			dir = 2;
		} else if (y == (yres() - r - 1)) {
			dir = 4;
		}
		break;
	case 4:
		if (x == r && y == r) {
			dir = 2;
		} else if (x == r) {
			dir = 1;
		} else if (y == r) {
			dir = 3;
		}
		break;
	}

	switch (dir) {
	case 1:
		x++; y--;
		break;
	case 2:
		x++; y++;
		break;
	case 3:
		x--; y++;
		break;
	case 4:
		x--; y--;
		break;
	}

	circle(x, y, r, color);
}

int main(void)
{
	int ret;

	ret = fb_open();
	if (ret != 0) {
		perror("fb_open()");
		return 1;
	}

	init();
	//circle(x, y, r, 0xff);

	while (1) {
		usleep(50000);
		move();
	}

	fb_close();
	return 0;
}
