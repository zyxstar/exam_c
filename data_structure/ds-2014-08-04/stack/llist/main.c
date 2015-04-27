#include <stdio.h>

#include "stack.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
};

int main(void)
{
	STACK *stack;
	struct score tmp;
	int i;
	int ret;
	int a;

	stack = stack_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 5; i++) {
		tmp.id = i + 1;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		stack_push(stack, &tmp);
		/* if error */
	}

	while (1) {
		ret = stack_pop(stack, &tmp);
		if (ret == -1) {
			break;
		}
		printf("%d %s\n", tmp.id, tmp.name);
	}

	stack_destroy(stack);

	return 0;
}
