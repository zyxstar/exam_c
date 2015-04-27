#include <stdlib.h>
#include <string.h>

#include "darr.h"

DARR *darr_creat(int size)
{
	DARR *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->num = 0;
	new->arr = NULL;

	new->key_cmp = NULL;
	new->data_cmp = NULL;

	return new;
}

DARR *darr_creat_sort(int size, darr_cmp *key_cmp, darr_cmp *data_cmp)
{
	DARR *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->num = 0;
	new->arr = NULL;

	new->key_cmp = key_cmp;
	new->data_cmp = data_cmp;

	return new;
}

void darr_set_sort(DARR *ptr, darr_cmp *key_cmp, darr_cmp *data_cmp)
{
	ptr->key_cmp = key_cmp;
        ptr->data_cmp = data_cmp;

	qsort(ptr->arr, ptr->num, ptr->size, data_cmp);
}

void darr_destroy(DARR *ptr)
{
	free(ptr->arr);
	free(ptr);
}

static int darr_bsearch_near(DARR *ptr, const void *data)
{
	int start, end, mid = 0;
	int ret;

	start = 0; end = ptr->num - 1;

	while (start <= end) {
		mid = (start + end) / 2;
		ret = ptr->data_cmp(data, ptr->arr + mid * ptr->size);
		if (ret == 0) {
			break;
		}
		if (ret < 0) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return mid;
}

static int darr_bsearch(DARR *ptr, const void *key)
{
	char *data;

	data = bsearch(key, ptr->arr, ptr->num, ptr->size, ptr->key_cmp);
	if (data == NULL) {
		return -1;
	}

	return (data - ptr->arr) / ptr->size;
}

int darr_insert(DARR *ptr, const void *data)
{
	char *tmp;
	int ind;

	tmp = realloc(ptr->arr, ptr->size * (ptr->num + 1));
	if (tmp == NULL) {
		return -1;
	}
	ptr->arr = tmp;

	if (ptr->num == 0 || ptr->data_cmp == NULL) {
		//memcpy(ptr->arr + ptr->size * ptr->num, data, ptr->size);
		ind = ptr->num;
	} else {
		ind = darr_bsearch_near(ptr, data);
		if (ptr->data_cmp(data, ptr->arr + ind * ptr->size) > 0) {
			ind++;
		}
	}

	memmove(ptr->arr + (ind + 1) * ptr->size, ptr->arr + ind  * ptr->size, ptr->size * (ptr->num - ind));
	memcpy(ptr->arr + ind  * ptr->size, data, ptr->size);
	ptr->num++;

	return 0;
}

void darr_delet(DARR *ptr, const void *key, darr_cmp *cmp)
{
	int i;
	char *tmp;

	if (cmp != NULL) {
		for (i = 0; i < ptr->num; i++) {
			if (cmp(key, ptr->arr + i * ptr->size) == 0) {
				break;
			}
		}
	} else {
		i = darr_bsearch(ptr, key);
	}

	if (i == ptr->num || i == -1) {
		return;
	}

	memmove(ptr->arr + i * ptr->size, ptr->arr + (i + 1) * ptr->size, (ptr->num - i - 1) * ptr->size);
	ptr->num--;

	ptr->arr = realloc(ptr->arr, ptr->size * ptr->num);
}

void *darr_search(DARR *ptr, const void *key, darr_cmp *cmp)
{
	int i;

	if (cmp != NULL) {
		for (i = 0; i < ptr->num; i++) {
			if (cmp(key, ptr->arr + i * ptr->size) == 0) {
				return ptr->arr + i * ptr->size;
			}
		}
	} else {
		i = darr_bsearch(ptr, key);
		if (i != -1) {
			return ptr->arr + i * ptr->size;
		}
	}

	return NULL;
}

void darr_travel(DARR *ptr, darr_op *op)
{
	int i;

	for (i = 0; i < ptr->num; i++) {
		op(ptr->arr + i * ptr->size);
	}
}
