#include <stdio.h>

int picture[16][22] = {
	{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,2,2,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,2,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
	{0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

void draw(void)
{
	int i, j;

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 22; j++) {
			switch (picture[i][j]) {
			case 0:
				printf(". ");
				break;
			case 1:
				printf("+ ");
				break;
			case 2:
				printf("B ");
				break;
			case 3:
				printf("O ");
				break;
			}
		}
		printf("\n");
	}
}

static int illeg(int y, int x)
{
	if (x < 0 || x >= 22) {
		return 1;
	}
	if (y < 0 || y >= 16) {
		return 1;
	}
	if (picture[y][x] != 0) {
		return 1;
	}
	return 0;
}

void paint__(int y, int x)
{
	if (illeg(y, x)) {
		return;
	}

	picture[y][x] = 1;
	draw();
	getchar();

	/* child 1 */
	paint__(y, x + 1);
	/* child 2 */
	paint__(y + 1, x);
	/* child 3 */
	paint__(y, x - 1);
	/* child 4 */
	paint__(y - 1, x);
}

void paint(void)
{
	int x, y;
	int i, j;

	for (i = 0; i < 16; i++) {
		for (j = 0; j < 22; j++) {
			if (picture[i][j] == 3) {
				picture[i][j] = 0;
				paint__(i, j);
				return;
			}
		}
	}
}

int main(void)
{
	draw();
	getchar();
	paint();

	return 0;
}
