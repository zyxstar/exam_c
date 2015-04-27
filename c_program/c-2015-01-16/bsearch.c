#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32

static void *binsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *));

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static int comp(const void *key, const void *data)
{
	const int *k = key;
	const struct score *d = data;

	return *k - d->id;
}

int main(void)
{
	struct score arr[] = {
		{1, "shrek", 80, 59},
		{3, "hsienmu", 99, 100},
		{5, "zorro", 80, 80},
		{7, "rose", 59, 58},
	};
	struct score *data;
	int id;

	int (*p)(const void *, const void *);
	p = comp;

	id = 5;
	//data = bsearch(&id, arr, 4, sizeof(struct score), comp);
	data = binsearch(&id, arr, 4, sizeof(struct score), p);
	if (data != NULL) {
		printf("%d, %s, %d, %d\n", data->id, data->name, data->ch, data->math);
	} else {
		printf("Can not find.\n");
	}

	return 0;
}

static void *binsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
	int start, end, mid;
	int ret;
	const char *b = base;

	start = 0; end = nmemb - 1;
	while (start <= end) {
		mid = (start + end) / 2;

		ret = cmp(key, b + mid * size);
		if (ret == 0) {
			return (void *)(b + mid * size);
		} else if (ret < 0) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return NULL;
}
