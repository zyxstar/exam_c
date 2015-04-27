#include <stdio.h>
#include <string.h>

#include "darr.h"

#define NAMESIZE  32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static void print_score(void *data)
{
	struct score *d = data;

	printf("%d, %s, %d, %d\n", d->id, d->name, d->ch, d->math);
}

static int id_cmp(const void *key, const void *data)
{
	const int *k = key;
	const struct score *d = data;
	return *k - d->id;
}

static int id_data_cmp(const void *data1, const void *data2)
{
	const struct score *d1 = data1;
	const struct score *d2 = data2;
	return d1->id - d2->id;
}

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;
	return strcmp(k, d->name);
}

int main(void)
{
	int id[] = {3,2,1,6,7};
	struct score tmp, *data;
	int id_val;
	int i;
	DARR *arr;

	arr = darr_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < sizeof(id) / sizeof(*id); i++) {
		tmp.id = id[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", id[i]);
		tmp.ch = 100 - id[i];
		tmp.math = 100 - id[i] * 2;

		darr_insert(arr, &tmp);
	}

	darr_travel(arr, print_score);
	printf("\n");
	darr_set_sort(arr, id_cmp, id_data_cmp);
	darr_travel(arr, print_score);

	printf("\n");
	id_val = 1;
#if 0
	//data = darr_search(arr, &id_val, NULL);
	data = darr_search(arr, "stu5", name_cmp);
	if (data == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(data);
	}
	darr_delet(arr, "stu5", name_cmp);
#endif
	darr_delet(arr, &id_val, NULL);
	darr_travel(arr, print_score);

	darr_destroy(arr);

	return 0;
}
