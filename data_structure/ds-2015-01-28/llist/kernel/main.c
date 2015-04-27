#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mylist.h"

#define NAMESIZE  32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
	struct list_head node;
};

int main(void)
{
	struct score *tmp, *data;
	int i;
	LIST_HEAD(list);	/* init head */
	//struct list_head list = {&list, &list};
	int ret;
	struct list_head *cur;

	for (i = 0; i < 7; i++) {
		tmp = malloc(sizeof(*tmp));
		/* if error */

		tmp->id = i;
		tmp->ch = 100 - i;
		tmp->math = 100 - 2 * i;
		snprintf(tmp->name, NAMESIZE, "stu%d", i);

		list_add(&tmp->node, &list);
	}

	/* travel */
	__list_for_each(cur, &list) {
		data = list_entry(cur, struct score, node);
		printf("%d, %s, %d, %d\n", data->id, data->name, data->ch, data->math);
	}

	/* delete */
	__list_for_each(cur, &list) {
                data = list_entry(cur, struct score, node);
		if (data->id == 3) {
			list_del(cur);
			free(data);
			break;
		}
	}

	printf("\n");
	__list_for_each(cur, &list) {
		data = list_entry(cur, struct score, node);
		printf("%d, %s, %d, %d\n", data->id, data->name, data->ch, data->math);
	}

	/* destroy */

	return 0;
}
