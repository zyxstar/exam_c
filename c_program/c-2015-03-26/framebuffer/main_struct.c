#include <stdio.h>
#include <stdlib.h>

#include "fb_draw.h"

#define CIRCLE_NUM    8
#define R             50

struct circle_st {
	int x, y, direct;
};

static struct circle_st circle_arr[CIRCLE_NUM];

static void init(void)
{
	int i;

	for (i = 0; i < CIRCLE_NUM; i++) {
		circle_arr[i].x = (unsigned)rand() % (xres() - 200) + 100;
		circle_arr[i].y = (unsigned)rand() % (yres() - 200) + 100;
		circle_arr[i].direct = (unsigned)rand() % 4 + 1;
	}
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
static int is_side(int ind)
{
	if (circle_arr[ind].x == R && circle_arr[ind].y == R) {
		return 8;
	}
	if (circle_arr[ind].x == R && circle_arr[ind].y == yres() - R - 1) {
		return 7;
	}
	if (circle_arr[ind].x == xres() - R - 1 && circle_arr[ind].y == R) {
		return 5;
	}
	if (circle_arr[ind].x == xres() - R - 1 && circle_arr[ind].y == yres() - R - 1) {
		return 6;
	}

	if (circle_arr[ind].x == R) {
		return 4;
	}
	if (circle_arr[ind].x == xres() - R - 1) {
		return 2;
	}

	if (circle_arr[ind].y == R) {
		return 1;
        }
        if (circle_arr[ind].y == yres() - R - 1) {
                return 3;
	}

	return 0;
}

static void change_dir(int ind)
{
	int side;

	if ((side = is_side(ind)) == 0) {
		return;
	}

	switch (side) {
	case 1:
		if (circle_arr[ind].direct == 1) {
			circle_arr[ind].direct = 2;
		} else {
			circle_arr[ind].direct = 3;
		}
		break;
	case 2:
		if (circle_arr[ind].direct == 1) {
			circle_arr[ind].direct = 4;
		} else {
			circle_arr[ind].direct = 3;
		}
		break;
	case 3:
		if (circle_arr[ind].direct == 2) {
			circle_arr[ind].direct = 1;
		} else {
			circle_arr[ind].direct = 4;
		}
		break;
	case 4:
		if (circle_arr[ind].direct == 3) {
			circle_arr[ind].direct = 2;
		} else {
			circle_arr[ind].direct = 1;
		}
		break;
	case 5:
		circle_arr[ind].direct = 3;
                break;
	case 6:
		circle_arr[ind].direct = 4;
                break;
	case 7:
		circle_arr[ind].direct = 1;
                break;
	case 8:
		circle_arr[ind].direct = 2;
                break;
	}
}

static void move(void)
{
	int i;

	for (i = 0; i < CIRCLE_NUM; i++) {
		change_dir(i);

		switch (circle_arr[i].direct) {
		case 1:
			circle_arr[i].x++;
			circle_arr[i].y--;
			break;
		case 2:
			circle_arr[i].x++;
			circle_arr[i].y++;
			break;
		case 3:
			circle_arr[i].x--;
			circle_arr[i].y++;
			break;
		case 4:
			circle_arr[i].x--;
			circle_arr[i].y--;
			break;
		}
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
	int i;

	for (i = 0; i < CIRCLE_NUM; i++) {
		circle(circle_arr[i].x, circle_arr[i].y, R, 0xff);
	}
}

static void clear(void)
{
	int i;

	for (i = 0; i < CIRCLE_NUM; i++) {
		circle(circle_arr[i].x, circle_arr[i].y, R, 0x0);
	}
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

     srand(getpid());
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
