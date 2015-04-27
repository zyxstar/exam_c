#include <stdio.h>
#include <string.h>

#include "llist.h"

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

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;

	return strcmp(k, d->name);
}

int main(void)
{
	struct score tmp, *p;
	LLIST *list;
	int i;
	int ret;

	list = llist_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - i * 2;
		tmp.en = 100 - i * 3;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		llist_add(list, &tmp, LLIST_ADD_FORWARD);
	}

	llist_travel(list, print_score);
	ret = llist_fetch(list, "stu6", name_cmp, &tmp);
	if (ret == -1) {
		printf("Can not find.\n");
	} else {
		print_score(&tmp);
	}
	printf("\n");
	llist_travel(list, print_score);
#if 0
	p = llist_find(list, "stuxx", name_cmp);
	if (p == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(p);
	}
#endif

	llist_destroy(list);
	return 0;
}
