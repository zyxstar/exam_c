#include <stdio.h>
#include <stdlib.h>

#include "fb_draw.h"

void block(int x, int y, int width, int high, int color)
{
	int i, j;

	for (i = x; i < x + width; i++) {
		for (j = y; j < y + high; j++) {
			fb_draw_point(i, j, color);
		}
	}
}

int main(void)
{
     int x, y;
     int ret;
     int i;

     ret = fb_open();
     if (ret != 0) {
	  fprintf(stderr, "fb_open() error.\n");
	  exit(1);
     }

     x = y = 50;
     for (i = 0; i < 300; i++) {
	     block(x, y, 200, 200, 0xff);
	     usleep(100000);
	     block(x, y, 200, 200, 0x0);
	     x++, y++;
     }

     fb_close();
     return 0;
}
