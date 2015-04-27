#include <stdio.h>

#define STACKSIZE 12

struct stick {
	int stack[STACKSIZE];
	int ind;
};

static struct stick arr[3] = {
	{{6,5,4,3,2,1}, 6},
};

static void display(void)
{
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < arr[i].ind; j++) {
			printf("%d ", arr[i].stack[j]);
		}
		for (; j < STACKSIZE; j++) {
			printf("- ");
		}
		printf("\n");
	}
}

static void push(int stick, int data)
{
	arr[stick].stack[arr[stick].ind] = data;
	arr[stick].ind++;
}

static int pop(int stick)
{
	arr[stick].ind--;
	return arr[stick].stack[arr[stick].ind];
}

static void move(int dest, int src)
{
	int val;
	val = pop(src);
	push(dest, val);

	display();
	getchar();
}

void hanoi(int dest, int src, int tmp, int n)
{
	if (n == 1) {
		move(dest, src);
		return;
	}

	hanoi(tmp, src, dest, n - 1);
	move(dest, src);
	hanoi(dest, tmp, src, n - 1);
}

int main(void)
{
	display();
	getchar();
	hanoi(2, 0, 1, 6);

	return 0;
}
