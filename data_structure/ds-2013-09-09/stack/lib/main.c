#include <stdio.h>
#include <string.h>

#include "stack.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
	int en;
};

static void print_score(void *data)
{
	struct score *d = data;
	printf("%d %s %d %d %d\n", d->id, d->name, d->ch, d->math, d->en);
}

int main(void)
{
	struct score tmp, *p;
	STACK *list;
	int i;
	int ret;

	list = stack_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - i * 2;
		tmp.en = 100 - i * 3;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		stack_push(list, &tmp);
	}

	while (1) {
		ret = stack_pop(list, &tmp);
		if (ret == -1) {
			printf("stack empty.\n");
			break;
		}
		print_score(&tmp);
	}

	stack_destroy(list);
	return 0;
}
