#include <stdio.h>

#define NUM 9

struct stick {
	int stick[NUM];
	int ind;
} hn[3] = {
	{{5,4,3,2,1}, 5},
	{{}, 0},
	{{}, 0},
};

static draw(void)
{
	int i, ind;

	for (ind = 0; ind < 3; ind++) {
		for (i = 0; i < NUM && i < hn[ind].ind; i++) {
			printf("%d ", hn[ind].stick[i]);
		}
		printf("-\n");
	}
}

static int pop(int ind)
{
	int plate;

	hn[ind].ind--;
	plate = hn[ind].stick[hn[ind].ind];

	return plate;
}

static void push(int ind, int plate)
{
	hn[ind].stick[hn[ind].ind] = plate;
	hn[ind].ind++;
}

static void move(int src, int dest)
{
	int plate;

	plate = pop(src);
	push(dest, plate);

	draw();
	getchar();
}

void hanoi(int src, int dest, int tmp, int n)
{
	if (n == 1) {
		move(src, dest);
		return;
	}

	hanoi(src, tmp, dest, n - 1);
	move(src, dest);
	hanoi(tmp, dest, src, n - 1);
}

int main(void)
{
	draw();
	hanoi(0, 2, 1, 5);
	draw();

	return 0;
}
