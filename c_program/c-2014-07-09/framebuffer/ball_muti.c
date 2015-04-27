#include <stdio.h>

#include "fb_draw.h"

struct ball {
	int x, y;
	int r;
	int color;
	int dir;
};

struct node_st {
	struct ball data;
	struct node_st *next;
};

static void insert(struct node_st **list, struct node_st *node)
{
	node->next = *list;
	*list = node;
}

static int init(struct node_st **list)
{
	int i;
	struct node_st *newnode;

	srand(getpid());

	*list = NULL;
	for (i = 0; i < 2; i++) {
		newnode = malloc(sizeof(*newnode));
		/* if error */

		newnode->data.r = 50;
		newnode->data.x = (unsigned)rand() % (xres() - 200) + 100;
		newnode->data.y = (unsigned)rand() % (yres() - 200) +100;
		newnode->data.color = (unsigned)rand() % (0xff - 0x30) + 0x30;
		newnode->data.dir = (unsigned)rand() % 4 + 1;

		insert(list, newnode);
	}

	return 0;
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

static void move__(int *x, int *y, int r, int color, int *dir)
{
	circle(*x, *y, r, 0);

	switch (*dir) {
	case 1:
		if (*x == (xres() - r - 1) && *y == r) {
			*dir = 3;
		} else if (*x == (xres() - r - 1)) {
			*dir = 4;
		} else if (*y == r) {
			*dir = 2;
		}
		break;
	case 2:
		if (*x == (xres() - r - 1) && *y == (yres() - r - 1)) {
			*dir = 4;
		} else if (*x == (xres() - r - 1)) {
			*dir = 3;
		} else if (*y == (yres() - r - 1)) {
			*dir = 1;
		}
		break;
	case 3:
		if (*x == r && *y == (yres() - r - 1)) {
			*dir = 1;
		} else if (*x == r) {
			*dir = 2;
		} else if (*y == (yres() - r - 1)) {
			*dir = 4;
		}
		break;
	case 4:
		if (*x == r && *y == r) {
			*dir = 2;
		} else if (*x == r) {
			*dir = 1;
		} else if (*y == r) {
			*dir = 3;
		}
		break;
	}

	switch (*dir) {
	case 1:
		(*x)++; (*y)--;
		break;
	case 2:
		(*x)++; (*y)++;
		break;
	case 3:
		(*x)--; (*y)++;
		break;
	case 4:
		(*x)--; (*y)--;
		break;
	}

	circle(*x, *y, r, color);
}

static void move(struct node_st *list)
{
	struct node_st *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		move__(&cur->data.x, &cur->data.y, cur->data.r, cur->data.color, &cur->data.dir);
	}
}

int main(void)
{
	int ret;
	struct node_st *list = NULL;

	ret = fb_open();
	if (ret != 0) {
		perror("fb_open()");
		return 1;
	}

	init(&list);
	/* if error */

	while (1) {
		usleep(50000);
		move(list);
	}

	fb_close();
	return 0;
}
