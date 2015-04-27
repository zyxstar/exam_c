#include <string.h>

#include "glob.h"
#include "display.h"
#include "move.h"

static void map_pos(const struct little_st *little, int y, int x, int *big_y, int *big_x)
{
	int base_x = little->x;
	int base_y = little->y;

	*big_x = x + base_x;
	*big_y = y + base_y - 3;
}

static int is_legal(const struct little_st *little)
{
	int i, j;
	int (*arrp)[4];
	int big_x, big_y;

	arrp = little_list[little->shape][little->dirc];

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (arrp[i][j] == 1) {
				map_pos(little, i, j, &big_y, &big_x);
				if (big_x < 0 || big_x >= 10) {
					/* debug */
					printf("illegal\n");
					return 0;
				}
				if (big_y >= 20) {
					/* debug */
					printf("illegal\n");
					return 0;
				}
				if (main_arr[big_y][big_x] == 1) {
					/* debug */
					printf("illegal\n");
					return 0;
				}
			}
		}
	}

	return 1;
}

void little2big(int arr[20][10])
{
	int i, j;
	int (*arrp)[4];
	int big_x, big_y;

	arrp = little_list[little.shape][little.dirc];

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (arrp[i][j] == 1) {
				map_pos(&little, i, j, &big_y, &big_x);
				if (big_y >= 0) {
					arr[big_y][big_x] = 1;
				}
			}
		}
	}
}

void init(void)
{
	init_little();
}

void init_little(void)
{
	little.shape = (unsigned)rand() % 3;
	little.dirc = (unsigned)rand() % 4;
	little.x = 3;
	little.y = 0;

	/* debug */
	printf("new little: shape = %d, dirc = %d\n", little.shape, little.dirc);
}

void move_left(void)
{
	struct little_st little_tmp;

	little_tmp = little;
	little_tmp.x--;

	if (!is_legal(&little_tmp)) {
		return;
	}

	little = little_tmp;
	memcpy(tmp_arr, main_arr, sizeof(main_arr));
	little2big(tmp_arr);

	display();
}

void move_right(void)
{
	struct little_st little_tmp;

	little_tmp = little;
	little_tmp.x++;

	if (!is_legal(&little_tmp)) {
		return;
	}

	little = little_tmp;
	memcpy(tmp_arr, main_arr, sizeof(main_arr));
	little2big(tmp_arr);

	display();
}

int move_down(void)
{
	struct little_st little_tmp;

	little_tmp = little;
	little_tmp.y++;

	if (!is_legal(&little_tmp)) {
		return -1;
	}

	little = little_tmp;
	memcpy(tmp_arr, main_arr, sizeof(main_arr));
	little2big(tmp_arr);

	display();

	return 0;
}

void roll(void)
{
	struct little_st little_tmp;

	little_tmp = little;
	//little_tmp.x--;
	little_tmp.dirc++;
	if (little_tmp.dirc == 4) {
		little_tmp.dirc = 0;
	}

	if (!is_legal(&little_tmp)) {
		return;
	}

	little = little_tmp;
	memcpy(tmp_arr, main_arr, sizeof(main_arr));
	little2big(tmp_arr);

	display();
}

static int line_full(int ind)
{
	int i;
	int full = 1;

	for (i = 0; i < 10; i++) {
		if (main_arr[ind][i] == 0) {
			full = 0;
		}
	}
	return full;
}

static void clear_line__(int ind)
{
	memmove(main_arr + 1, main_arr, ind * sizeof(*main_arr));
	memset(main_arr, 0, (20 - ind) * sizeof(*main_arr));
}

void clear_line(void)
{
	int i;

	i = 19;
	while (i >= 0) {
		if (line_full(i)) {
			clear_line__(i);
		} else {
			i--;
		}
	}
}
