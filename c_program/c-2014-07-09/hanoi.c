#include <stdio.h>

struct {
	int stick[7];
	int ind;
} hanoi_arr[3] = {
	{{7,6,5,4,3,2,1}, 7},
};

void display(void)
{
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < hanoi_arr[i].ind; j++) {
			printf("%d", hanoi_arr[i].stick[j]);
		}
		for (; j < 8; j++) {
			printf("-");
		}
		printf("\n");
	}

	getchar();
}

void move(int src, int dest)
{
	int tmp;

	hanoi_arr[src].ind--;
	tmp = hanoi_arr[src].stick[hanoi_arr[src].ind];

	hanoi_arr[dest].stick[hanoi_arr[dest].ind] = tmp;
	hanoi_arr[dest].ind++;

	display();
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
	display();
	hanoi(0, 1, 2, 6);

	return 0;
}
