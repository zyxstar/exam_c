#include <stdio.h>

#include "darr.h"

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

static void print_score(void *data)
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

static int name_cmp(const void *key, const void *data)
{
	const struct score *d = data;

	return strcmp(key, d->name);
}

static int id_cmp(const void *key, const void *data)
{
	const int *id = key;
	const struct score *d = data;

	return -(*id - d->id);
}

static int id_data_cmp(const void *data1, const void *data2)
{
	const struct score *d1 = data1;
	const struct score *d2 = data2;

	return -(d1->id - d2->id);
}

int main(void)
{
	DARR *darr;
	int arr[] = {6,7,2,1,3,4,5};
	struct score tmp, *datap;
	int i;
	int id;
	struct sum_st sum = {0,0};

	darr = darr_creat_sort(sizeof(struct score), id_cmp, id_data_cmp);
	/* if error */

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
		tmp.ch = 100 - arr[i];
		tmp.math = 100 - 2 * arr[i];

		darr_insert(darr, &tmp);
		/* if error */
	}

	darr_travel(darr, print_score);
	printf("\n");

#if 1
	id = 40;
	//darr_delet(darr, &id, NULL);
	darr_delet(darr, "stu3", name_cmp);
	darr_travel(darr, print_score);
#else
	darr_travel_adv(darr, get_sum, &sum);
	printf("sum: ch = %d, math = %d\n", sum.ch, sum.math);
	//datap = darr_find(darr, &id, NULL);
	datap = darr_find(darr, "xxx", name_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(datap);
	}
	darr_sort(darr, id_cmp, id_data_cmp);
	darr_travel(darr, print_score);
#endif

	darr_destroy(darr);

	return 0;
}
