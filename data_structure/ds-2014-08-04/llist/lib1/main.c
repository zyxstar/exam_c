#include <stdio.h>

#include "llist.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

struct sum_st {
	int ch;
	int math;
};

static void print_score(void *data, void *unuse)
{
	struct score *d = data;

	printf("%d %s %d %d\n", d->id, d->name, d->ch, d->math);
}

static void get_sum(void *data, void *sum)
{
	struct score *d = data;
	struct sum_st *s = sum;

	s->ch += d->ch;
	s->math += d->math;
}

static int id_cmp(const void *key, const void *data)
{
	const int *id = key;
	const struct score *d = data;

	return *id - d->id;
}

int main(void)
{
	LLIST *llist;
	struct score tmp, *datap;
	int i;
	int id;
	struct sum_st sum = {0,0};

	llist = llist_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 7; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		llist_insert(llist, &tmp);
		/* if error */
	}

	llist_travel(llist, print_score, NULL);
	printf("\n");

#if 1
	id = 3;
	llist_delet(llist, &id, id_cmp);
	llist_travel(llist, print_score, NULL);
#else
	datap = llist_find(llist, &id, id_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(datap, NULL);
	}
	llist_travel(llist, get_sum, &sum);
	printf("sum: ch = %d, math = %d\n", sum.ch, sum.math);
#endif

	llist_destroy(llist);

	return 0;
}
