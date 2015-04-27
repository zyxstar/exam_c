#include <stdio.h>

#define BUFSIZE 64

enum COLOR {BLANK, BLACK, WHITE};

static enum COLOR color = BLACK;
static int pan[9][9] = {
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
	{0,0,0,0,0,0,0,0,0,},
};
static int x, y;

static void display(void)
{
	int i, j;

	system("clear");

	printf(" ");
	for (i = 1; i <= 9; i++) {
		printf(" %d", i);
	}
	printf("\n");

	for (i = 0; i < 9; i++) {
		printf("%d ", i + 1);
		for (j = 0; j < 9; j++) {
			if (pan[i][j] == 0) {
				printf("+ ");
			} else if (pan[i][j] == 1) {
				printf("B ");
			} else {
				printf("O ");
			}
		}
		printf("\n");
	}
}

static void input(void)
{
	char buf[BUFSIZE];

	if (color == BLACK) {
		printf("BLACK:\n");
	} else {
		printf("WHITE:\n");
	}

	fgets(buf, BUFSIZE, stdin);
	x = atoi(buf) - 1;
	fgets(buf, BUFSIZE, stdin);
        y = atoi(buf) - 1;

	if (x >= 0 && x < 9 && y >= 0 && y < 9 \
	    && pan[y][x] == BLANK) {
		pan[y][x] = color;
		if (color == BLACK) {
			color = WHITE;
		} else {
			color = BLACK;
		}
	}
}

static int win(void)
{
	int sum;
	int i, j;

	sum = 1;
	/* dir 1 */
	j = x;
	for (i = y - 1; i >= 0; i--) {
		if (pan[i][j] != pan[y][x]) {
			break;
		}
		sum++;
	}
	for (i = y + 1; i < 9; i++) {
                if (pan[i][j] != pan[y][x]) {
                        break;
                }
                sum++;
        }
	if (sum >= 5) {
		return 1;
	}

	sum = 1;
	/* dir 2 */
	for (i = y + 1, j = x - 1; i < 9 && j >= 0; i++, j--) {
		if (pan[i][j] != pan[y][x]) {
			break;
		}
		sum++;
	}
	for (i = y - 1, j = x + 1; i >= 0 && j < 9; i--, j++) {
                if (pan[i][j] != pan[y][x]) {
                        break;
                }
                sum++;
        }
	if (sum >= 5) {
		return 1;
	}

	return 0;
}

int main(void)
{
	int ret;

	display();

	while (1) {
		input();
		display();
		ret = win();
		if (ret) {
			break;
		}
	}

	return 0;
}
