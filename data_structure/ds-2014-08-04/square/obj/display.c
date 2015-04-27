#include "display.h"

#define TOP_BASE 50
#define LEFT_BASE 270

static void draw_square(int y, int x, int width, int high, int color)
{
	int i, j;

	//fprintf(stderr, "in %s(), x = %d, y = %d, w = %d, h = %d\n", __func__, x, y, width, high);

	for (i = y; i < y + high; i++) {
		for (j = x; j < x + width; j++) {
			fb_draw_point(j, i, color);
		}
	}
}

static void draw_block(int y, int x, int bool)
{
	if (bool) {
		draw_square(TOP_BASE + y * 25 + 1, LEFT_BASE + x * 25 + 1, 23, 23, 0x30);
	} else {
		draw_square(TOP_BASE + y * 25 + 1, LEFT_BASE + x * 25 + 1, 23, 23, 0xaf);
	}
}

void display(void)
{
	int i, j;

	for (i = TOP_BASE; i < TOP_BASE + 25 * 20; i++) {
		for (j = LEFT_BASE; j < LEFT_BASE + 25 * 10; j++) {
			fb_draw_point(j, i, 0xff);
		}
	}

	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			draw_block(i, j, tmp_arr[i][j]);
		}
	}
}
