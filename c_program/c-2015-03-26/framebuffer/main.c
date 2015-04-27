#include <stdio.h>
#include <stdlib.h>

#include "fb_draw.h"

#define R 50

static int x, y, direct;

static void init(void)
{
	srand(getpid());
	x = (unsigned)rand() % (xres() - 200) + 100;
	y = (unsigned)rand() % (yres() - 200) + 100;
	direct = (unsigned)rand() % 4 + 1;
}

/*********************
 ******** side *******

      8    1    5
       *********
       *********
      4*********2
       *********
       *********
      7    3    6

 *********************/
static int is_side(void)
{
	if (x == R && y == R) {
		return 8;
	}
	if (x == R && y == yres() - R - 1) {
		return 7;
	}
	if (x == xres() - R - 1 && y == R) {
		return 5;
	}
	if (x == xres() - R - 1 && y == yres() - R - 1) {
		return 6;
	}

	if (x == R) {
		return 4;
	}
	if (x == xres() - R - 1) {
		return 2;
	}

	if (y == R) {
		return 1;
        }
        if (y == yres() - R - 1) {
                return 3;
	}

	return 0;
}

static void change_dir(void)
{
	int side;

	if ((side = is_side()) == 0) {
		return;
	}

	switch (side) {
	case 1:
		if (direct == 1) {
			direct = 2;
		} else {
			direct = 3;
		}
		break;
	case 2:
		if (direct == 1) {
			direct = 4;
		} else {
			direct = 3;
		}
		break;
	case 3:
		if (direct == 2) {
			direct = 1;
		} else {
			direct = 4;
		}
		break;
	case 4:
		if (direct == 3) {
			direct = 2;
		} else {
			direct = 1;
		}
		break;
	case 5:
		direct = 3;
                break;
	case 6:
		direct = 4;
                break;
	case 7:
		direct = 1;
                break;
	case 8:
		direct = 2;
                break;
	}
}

static void move(void)
{
	change_dir();

	switch (direct) {
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
}

static void circle(int x, int y, int r, int color)
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

static void draw(void)
{
	circle(x, y, R, 0xff);
}

static void clear(void)
{
	circle(x, y, R, 0x0);
}

int main(void)
{
     int x, y;
     int ret;

     ret = fb_open();
     if (ret != 0) {
	  fprintf(stderr, "fb_open() error.\n");
	  exit(1);
     }

     init();
     while (1) {
	     draw();
	     usleep(10000);
	     clear();
	     move();
     };

     fb_close();
     return 0;
}
