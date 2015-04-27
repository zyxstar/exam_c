#include <stdio.h>

#include "darr.h"
#include "debug.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

void print_score(void *d)
{
	struct score *data = d;

	printf("%d %s %d %d\n", data->id, data->name, data->ch, data->math);
}

int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;

	return strcmp(k, d->name);
}

int main(void)
{
	struct score tmp, *datap;
	int i;
	DARR *darr;

	darr = darr_creat(sizeof(struct score));
	/* if error */

	debug1("%s(): darr_creat() return %p\n", __func__, darr);

	debug("debug\n");

	for (i = 0; i < 6; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - i * 2;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		darr_insert(darr, &tmp);
	}

	darr_travel(darr, print_score);

	printf("\n");
	darr_delet(darr, "stu2", name_cmp);
	darr_travel(darr, print_score);
#if 0
	datap = darr_find(darr, "stu2", name_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(datap);
	}
#endif
	darr_destroy(darr);

	return 0;
}
