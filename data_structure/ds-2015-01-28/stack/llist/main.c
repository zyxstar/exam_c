#include <stdio.h>

#include "stack.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
};

int main(void)
{
	STACK *stack;
	struct score tmp;
	int i;
	int ret;

	stack = stack_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;

		stack_push(stack, &tmp);
		/* if error */
	}

	while (1) {
		ret = stack_pop(stack, &tmp);
		if (ret == -1) {
			break;
		}

		printf("%d, %s, %d\n", tmp.id, tmp.name, tmp.ch);
	}

	stack_destroy(stack);

	return 0;
}
