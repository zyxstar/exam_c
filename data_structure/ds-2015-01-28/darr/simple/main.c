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

static int insert(struct score **arr, int *num, struct score *data)
{
	struct score *tmp;

	tmp = malloc(sizeof(struct score) * (*num + 1));
	if (tmp == NULL) {
		return -1;
	}

	memcpy(tmp, *arr, *num * sizeof(struct score));
	tmp[*num] = *data;
	(*num)++;

	free(*arr);
	*arr = tmp;

	return 0;
}

static void travel(struct score *arr, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		printf("%d, %s, %d, %d\n", arr[i].id, arr[i].name, arr[i].ch, arr[i].math);
	}
}

static void delete(struct score **arr, int *num, int id)
{
	int i;
	struct score *tmp;

	for (i = 0; i < *num; i++) {
		if ((*arr)[i].id == id) {
			break;
		}
	}

	if (i == *num) {
		return;
	}

	memmove(*arr + i, *arr + i + 1, (*num - i - 1) * sizeof(struct score));
	(*num)--;

	tmp = malloc(sizeof(*tmp) * *num);
	if (tmp == NULL) {
		return;
	}

	memcpy(tmp, *arr, sizeof(*tmp) * *num);
	free(*arr);
	*arr = tmp;
}

int main(void)
{
	struct score *arr = NULL;
	int arr_num = 0;
	int id[] = {3,2,1,6,7};
	int i;
	struct score tmp;

	for (i = 0; i < sizeof(id) / sizeof(*id); i++) {
		tmp.id = id[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", id[i]);
		tmp.ch = 100 - id[i];
		tmp.math = 100 - id[i] * 2;

		insert(&arr, &arr_num, &tmp);
	}

	travel(arr, arr_num);
	delete(&arr, &arr_num, 70);
	printf("\n");
	travel(arr, arr_num);

	free(arr);

	return 0;
}
