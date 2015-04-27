#include <stdio.h>
#include <string.h>

#include <llist.h>

#define NAMESIZE  32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static void print_score(void *data, void *unuse)
{
	struct score *d = data;

	printf("%d, %s, %d, %d\n", d->id, d->name, d->ch, d->math);
}

#define ID_NR  64
struct arr_st {
	int id[ID_NR];
	int ind;
};

static void getlist(void *data, void *array)
{
	struct arr_st *arr = array;
	struct score *d = data;

	arr->id[arr->ind] = d->id;
	arr->ind++;
}

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;
	return strcmp(k, d->name);
}

int main(void)
{
	struct score tmp, *data;
	int i;
	LLIST *list;
	int ret;

	list = llist_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 7; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		llist_insert(list, &tmp, DIR_BACK);
	}

	llist_travel(list, print_score, NULL);

	printf("\n");
	ret = llist_fetch(list, &tmp, "stu4", name_cmp);
	if (ret == -1) {
		printf("Can not find.\n");
	} else {
                print_score(&tmp, NULL);
        }
	printf("\n");
	llist_travel(list, print_score, NULL);

#if 0
	data = llist_search(list, "stu30", name_cmp);
	if (data == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(data, NULL);
	}
	struct arr_st arr = {.ind = 0};
	llist_travel(list, getlist, &arr);
	for (i = 0; i < arr.ind; i++) {
		printf("%d ", arr.id[i]);
	}
	printf("\n");
#endif
	llist_save(list, "tmp");

	llist_destroy(list);
	return 0;
}
