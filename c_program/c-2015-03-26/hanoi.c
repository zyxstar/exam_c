#include <stdio.h>

#define STICK_NUM 10

struct {
	int stick[STICK_NUM];
	int ind;
} hanoi_arr[3] = {
	{{6,5,4,3,2,1}, 6},
	{},
	{},
};

static void hanoi_print(void)
{
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < hanoi_arr[i].ind; j++) {
			printf("%d ", hanoi_arr[i].stick[j]);
		}
		for (; j < 8; j++) {
			printf("- ");
		}
		printf("\n");
	}
	getchar();
}

static void push(int stack, int data)
{
	hanoi_arr[stack].stick[hanoi_arr[stack].ind] = data;
	hanoi_arr[stack].ind++;
}

static int pop(int stack)
{
	hanoi_arr[stack].ind--;
	return hanoi_arr[stack].stick[hanoi_arr[stack].ind];
}

static void move(int src, int dest)
{
	push(dest, pop(src));
	hanoi_print();
}

void hanoi(int n, int src, int dest, int tmp)
{
	if (n == 1) {
		move(src, dest);
		return;
	}

	hanoi(n - 1, src, tmp, dest);
	move(src, dest);
	hanoi(n - 1, tmp, dest, src);
}

int main(void)
{
	hanoi_print();
	hanoi(6, 0, 2, 1);

	return 0;
}
