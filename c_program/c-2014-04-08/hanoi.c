#include <stdio.h>

#define STACK_NR 16

struct stick {
	int stack[STACK_NR];
	int ind;
} stick_arr[3];

void hanoi_init(int n)
{
	int i, j;

	for (i = n, j = 0; i > 0; i--, j++) {
		stick_arr[0].stack[j] = i;
	}
	stick_arr[0].ind = n;

	stick_arr[1].ind = 0;
	stick_arr[2].ind = 0;
}

void display(void)
{
	int i, j;

	for (i = 0; i < 3; i++) {
		printf("  ");
		for (j = 0; j < stick_arr[i].ind; j++) {
			printf("%d", stick_arr[i].stack[j]);
		}
		printf("-\n");
	}
	getchar();
}

static void push(int arr_ind, int data)
{
	stick_arr[arr_ind].stack[stick_arr[arr_ind].ind] = data;
	stick_arr[arr_ind].ind++;
}

static int pop(int arr_ind)
{
	stick_arr[arr_ind].ind--;
	return stick_arr[arr_ind].stack[stick_arr[arr_ind].ind];
}

static void move(int src, int dest)
{
	int ret;
	ret = pop(src);
	push(dest, ret);
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
	hanoi_init(6);
	display();
	hanoi(0, 1, 2, 6);

	return 0;
}
