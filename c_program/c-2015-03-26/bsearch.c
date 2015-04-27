#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 32
struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static int id_cmp(const void *key, const void *data)
{
	const int *k = key;
	const struct score *d = data;

	return *k - d->id;
}

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;

	return strcmp(k, d->name);
}

int main(void)
{
	struct score arr[] = {
		{5, "blues", 59, 70},
		{6, "john", 91, 93},
		{1, "hsienmu", 100, 100},
		{0, "shrek", 80, 59},
		{4, "xxx", 99, 99},
		{3, "zorro", 90, 90},
	};
	int i;
	int key = 5;
	struct score *datap;

	//datap = bsearch(&key, arr, 6, sizeof(*arr), id_cmp);
	datap = bsearch("xxx", arr, 6, sizeof(*arr), name_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s %d %d\n", datap->id, datap->name, datap->ch, datap->math);
	}

	return 0;
}
