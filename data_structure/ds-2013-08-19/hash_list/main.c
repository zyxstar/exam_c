#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE 32
#define LIST_NR 257

struct stu {
	int id;
	char name[NAMESIZE];
};

static LLIST *list[LIST_NR];

int init(void)
{
	int i, j;

	for (i = 0; i < LIST_NR; i++) {
		list[i] = llist_creat(sizeof(struct stu));
		if (list[i] == NULL) {
			for (j = 0; j < i; j++) {
				llist_destroy(list[j]);
			}
			return -1;
		}
	}
	return 0;
}

static void print_stu(struct stu *data)
{
	printf("%d %s\n", data->id, data->name);
}

static unsigned int hash(const char *data)
{
	unsigned int sum = 0;

	while (*data != '\0') {
		sum = (sum << 5) ^ *data;
		data++;
	}

	return sum;
}

int insert(struct stu *data)
{
	int ind;

	ind = hash(data->name) % LIST_NR;
	return llist_add(list[ind], data, LLIST_ADD_FORWARD);
}

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct stu *d = data;

	return strcmp(k, d->name);
}

struct stu *find(const char *name)
{
	int ind;

	ind = hash(name) % LIST_NR;
	return llist_find(list[ind], name, name_cmp);
}

static void rand_name(char *name, int size)
{
	int num;
	int i;

	num = (unsigned)rand() % (size - 4) + 4;
	for (i = 0; i < num; i++) {
		name[i] = (unsigned)rand() % 26 + 'a';
	}
	name[i] = '\0';
}

int main(void)
{
	struct stu tmp, *p;
	int i;
	int ret;

	srand(getpid());

	ret = init();
	if (ret == -1) {
		fprintf(stderr, "init() failed.\n");
		return 1;
	}

	for (i = 0; i < 8192 * 16; i++) {
		tmp.id = i;
		//snprintf(tmp.name, NAMESIZE, "stu%d", i);
		rand_name(tmp.name, NAMESIZE);

		insert(&tmp);
	}

	for (i = 0; i < LIST_NR; i++) {
		printf("%d ", llist_get_num(list[i]));
		if (i % 16 == 0 && i > 0) {
			printf("\n");
		}
	}
	printf("\n");

#if 0
	p = find("stu30");
	if (p == NULL) {
		printf("Can not find.\n");
	} else {
		print_stu(p);
	}
#endif
	return 0;
}
