#include "fb_draw.h"

struct point {
	int x, y;
};

struct circle {
	struct point cent;
	int r;
	int dir;
	int color;
};

#define BOX_SIZE 6
static struct circle box[BOX_SIZE];

void init(void)
{
	int i;

	srand(getpid());

	for (i = 0; i < BOX_SIZE; i++) {
		box[i].cent.x = (unsigned)rand() % (xres() - 200) + 100;
		box[i].cent.y = (unsigned)rand() % (yres() - 200) + 100;
		box[i].dir = (unsigned)rand() % 4;
		box[i].r = 50;
		box[i].color = 0xaf;
	}
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

static void move__(struct circle *p)
{
	circle(p->cent.x, p->cent.y, p->r, 0);

	switch (p->dir) {
	case 0:
		p->cent.x++; p->cent.y--;
		break;
	case 1:
		p->cent.x++; p->cent.y++;
		break;
	case 2:
		p->cent.x--; p->cent.y++;
		break;
	case 3:
		p->cent.x--; p->cent.y--;
		break;
	}
	circle(p->cent.x, p->cent.y, p->r, p->color);
}

void move(void)
{
	int ind;

	for (ind = 0; ind < BOX_SIZE; ind++) {
		move__(box + ind);
	}
}

static void change_dir__(struct circle *p)
{
	if (p->cent.x - p->r == 0 && p->cent.y - p->r == 0) {
		p->dir = 1;
	} else if (p->cent.x - p->r == 0 && p->cent.y + p->r == yres() - 1) {
		p->dir = 0;
	} else if (p->cent.x + p->r == xres() - 1 && p->cent.y - p->r == 0) {
		p->dir = 2;
	} else if (p->cent.x + p->r == xres() - 1 && p->cent.y + p->r == yres() - 1) {
		p->dir = 3;
	} else if (p->cent.x - p->r == 0) {
		if (p->dir == 2) {
			p->dir = 1;
		} else {
			p->dir = 0;
		}
	} else if (p->cent.x + p->r == xres() - 1) {
		if (p->dir == 0) {
			p->dir = 3;
		} else {
			p->dir = 2;
		}
	} else if (p->cent.y - p->r == 0) {
		if (p->dir == 0) {
			p->dir = 1;
		} else {
			p->dir = 2;
		}
	} else if (p->cent.y + p->r == yres() - 1) {
		if (p->dir == 1) {
			p->dir = 0;
		} else {
			p->dir = 3;
		}
	}
}

void change_dir(void)
{
        int ind;

        for (ind = 0; ind < BOX_SIZE; ind++) {
                change_dir__(box + ind);
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
