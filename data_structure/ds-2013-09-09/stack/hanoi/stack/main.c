#include <stdio.h>

#include "stack.h"

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

struct argment {
	int src, dest, tmp, n;
	int return_addr;
};

void hanoi(int src, int dest, int tmp, int n)
{
	struct argment val, tmp_val;
	STACK *stack;
	int ret;

	stack = stack_creat(sizeof(struct argment));

	val.src = src;
	val.dest = dest;
	val.tmp = tmp;
	val.n = n;

	while (1) {
		if (val.n == 1) {
			move(val.src, val.dest);
			//return;
			tmp_val = val;
			ret = stack_pop(stack, &val);
			if (ret == -1) {
				stack_destroy(stack);
				return;
			}

			if (tmp_val.return_addr == 1) {
				goto first;
			} else {
				goto second;
			}
		}

		//hanoi(src, tmp, dest, n - 1);
		stack_push(stack, &val);
		tmp_val = val;
		val.src = tmp_val.src;
		val.dest = tmp_val.tmp;
		val.tmp = tmp_val.dest;
		val.n = tmp_val.n - 1;
		val.return_addr = 1;
		continue;

	first:
		move(val.src, val.dest);

		//hanoi(tmp, dest, src, n - 1);
		stack_push(stack, &val);
		tmp_val = val;
		val.src = tmp_val.tmp;
		val.dest = tmp_val.dest;
		val.tmp = tmp_val.src;
		val.n = tmp_val.n - 1;
		val.return_addr = 2;
		continue;

	second:
		// return;
		tmp_val = val;
		ret = stack_pop(stack, &val);
		if (ret == -1) {
			stack_destroy(stack);
			return;
		}
		if (tmp_val.return_addr == 1) {
			goto first;
		} else {
			goto second;
		}
	}
}

int main(void)
{
	draw();
	hanoi(0, 2, 1, 5);
	draw();

	return 0;
}
