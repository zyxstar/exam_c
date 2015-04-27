#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int math;
};

int id_cmp(const void *key, const void *data)
{
	const int *k = key;
	const struct score *d = data;

	return *k - d->id;
}

int main(void)
{
	struct score arr[] = {{0, "shrek", 59}, {1, "hsienmu", 100}, {2, "blues", 80}, {3, "zorro", 99}};
	int id;
	struct score *datap;

	id = 3;
	datap = bsearch(&id, arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), id_cmp);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s %d\n", datap->id, datap->name, datap->math);
	}

	return 0;
}
