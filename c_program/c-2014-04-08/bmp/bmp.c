#include <stdio.h>

#include "fb_draw.h"

struct file_head_st {
	unsigned short magic_num;
	unsigned long size;
	unsigned long reserved;
	long offset;
} __attribute__ ((__packed__));

struct bitmap_head_st {
	unsigned long size;
	long width;
	long height;
	short plane;
	short bitcount;
	unsigned long biCompression;
	unsigned long biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	unsigned long biClrUsed;
	unsigned long biClrImportant;
} __attribute__ ((__packed__));

/* fix me */
#define BUFSIZE 4096

static void display_pix(int x, int y, char *color)
{
	fb_draw_point_24(x, y, color);
}

static void display_line(FILE *fp, int w, int line_len, int x, int y)
{
	char buf[BUFSIZE];
	int i;

	fread(buf, line_len, 1, fp);
	/* if error */

	for (i = 0; i < w; i++) {
		display_pix(x + i, y, buf + i * 3);
	}
}

void display(FILE *fp, int x, int y)
{
	struct file_head_st fhead;
	struct bitmap_head_st bhead;
	int w, h;
	int line_len;
	int i;

	fseek(fp, 0, SEEK_SET);

	fread(&fhead, sizeof(fhead), 1, fp);
	fread(&bhead, sizeof(bhead), 1, fp);

	w = bhead.width;
	h = bhead.height;
	line_len = (w * 3 + 4 - 1) & ~(4 - 1);

	fseek(fp, fhead.offset, SEEK_SET);
	for (i = 0; i < h; i++) {
		display_line(fp, w, line_len, x, y + h - i - 1);
	}
}

/* $ ./a.out xxx.bmp x y */
int main(int argc, char **argv)
{
	FILE *fp;
	int ret;
	int x, y;

	if (argc != 4) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	x = atoi(argv[2]);
	y = atoi(argv[3]);

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror(argv[1]);
		return 1;
	}

	ret = fb_open();
	if (ret == -1) {
		perror("framebuffer");
		fclose(fp);
		return 1;
	}

	display(fp, x, y);

	fb_close();
	fclose(fp);

	return 0;
}
