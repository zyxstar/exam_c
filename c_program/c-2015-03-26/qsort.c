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

static int id_cmp(const void *data1, const void *data2)
{
	const struct score *d1 = data1;
	const struct score *d2 = data2;

	return d1->id - d2->id;
}

static int name_cmp(const void *data1, const void *data2)
{
	const struct score *d1 = data1;
	const struct score *d2 = data2;

	return -strcmp(d1->name, d2->name);
}

static void swap(void *base1, void *base2, size_t size)
{
	char *p1 = base1;
	char *p2 = base2;
	int i;
	char tmp;

	for (i = 0; i < size; i++) {
		tmp = p1[i];
		p1[i] = p2[i];
		p2[i] = tmp;
	}
}

void myqsort(void *base, size_t nmemb, size_t size, int(*cmp)(const void *, const void *))
{
	int i, j;
	int ret;
	char *ptr = base;

	for (j = 0; j < nmemb - 1; j++) {
		for (i = 0; i < nmemb - 1 - j; i++) {
			ret = cmp(ptr + i * size, ptr + (i + 1) * size);
			if (ret > 0) {
				swap(ptr + i * size, ptr + (i + 1) * size, size);
			}
		}
	}
}

int main(void)
{
	struct score arr[] = {
		{1, "hsienmu", 100, 100},
		{5, "blues", 59, 70},
		{0, "shrek", 80, 59},
		{3, "zorro", 90, 90},
		{6, "john", 91, 93},
		{4, "xxx", 99, 99},
	};
	int i;

	myqsort(arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), name_cmp);
	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		printf("%d %s %d %d\n", arr[i].id, arr[i].name, arr[i].ch, arr[i].math);
	}

	return 0;
}
