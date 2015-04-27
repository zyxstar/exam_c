#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
	struct list_head node;
};

static void print_score(void *data)
{
	struct score *d = data;

	printf("%d %s %d %d\n", d->id, d->name, d->ch, d->math);
}

int main(void)
{
	LIST_HEAD(llist);
	struct list_head *cur;
	struct score *tmp, *datap;
	int i;

	for (i = 0; i < 7; i++) {
		tmp = malloc(sizeof(*tmp));
		/* if error */

		tmp->id = i;
		snprintf(tmp->name, NAMESIZE, "stu%d", i);
		tmp->ch = 100 - i;
		tmp->math = 100 - 2 * i;

		list_add(&tmp->node, &llist);
	}

	__list_for_each(cur, &llist) {
		datap = list_entry(cur, struct score, node);
		print_score(datap);
	}
	printf("\n");

	__list_for_each(cur, &llist) {
                datap = list_entry(cur, struct score, node);
		if (datap->id == 3) {
			break;
		}
        }
	list_del(cur);
	datap = list_entry(cur, struct score, node);
	free(datap);

	__list_for_each(cur, &llist) {
                datap = list_entry(cur, struct score, node);
                print_score(datap);
        }

	return 0;
}
