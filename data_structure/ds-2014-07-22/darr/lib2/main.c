#include <stdio.h>

#include "darr.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static void print_score(void *data)
{
	struct score *d = data;

	printf("%d %s %d %d\n", d->id, d->name, d->ch, d->math);
}

static int id_cmp(const void *key, const void *data)
{
	const int *id = key;
	const struct score *d = data;

	return *id - d->id;
}

int main(void)
{
	DARR *darr;
	struct score tmp, *datap;
	int i;
	int id;

	darr = darr_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		darr_insert(darr, &tmp);
		/* if error */
	}

	darr_travel(darr, print_score);
	printf("\n");

	id = 5;
#if 1
	darr_delet(darr, &id, id_cmp);
	darr_travel(darr, print_score);
#else
	datap = darr_find(darr, &id, id_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(datap);
	}
#endif

	darr_destroy(darr);

	return 0;
}
