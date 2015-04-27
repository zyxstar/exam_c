#include <stdio.h>
#include <stdlib.h>

#include "fb_draw.h"

struct fb_st {
     struct fb_fix_screeninfo fix;
     struct fb_var_screeninfo var;
     unsigned long bpp;
     int fd;
     char *fbp;
};

extern struct fb_st fb0;

int main(void)
{
     int x, y;
     int ret;
     int *p;

     ret = fb_open();
     if (ret != 0) {
	  fprintf(stderr, "fb_open() error.\n");
	  exit(1);
     }

     for (y = 300; y < 400; y++) {
	     for (x = 300; x < 400; x++) {
		     p = (int *)(fb0.fbp + y * fb0.fix.line_length + x * fb0.bpp);
		     *p = 0xff00ff;
	     }
     }

     fb_close();
     return 0;
}
