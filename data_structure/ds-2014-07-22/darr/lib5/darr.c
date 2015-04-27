#include <stdlib.h>
#include <string.h>

#include "darr.h"

struct darr_st {
	int size;
	int num;
	char *ptr;
	darr_cmp *key_cmp;
	darr_cmp *data_cmp;
};

DARR *darr_creat(int size)
{
	struct darr_st *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->num = 0;
	new->ptr = NULL;

	new->key_cmp = new->data_cmp = NULL;

	return new;
}

DARR *darr_creat_sort(int size, darr_cmp *key_cmp, darr_cmp *data_cmp)
{
	struct darr_st *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->num = 0;
	new->ptr = NULL;

	new->key_cmp = key_cmp;
	new->data_cmp = data_cmp;

	return new;
}

void darr_sort(DARR *box, darr_cmp *key_cmp, darr_cmp *data_cmp)
{
	struct darr_st *darr = box;

	darr->key_cmp = key_cmp;
	darr->data_cmp = data_cmp;

	qsort(darr->ptr, darr->num, darr->size, darr->data_cmp);
}

void darr_destroy(DARR *box)
{
	struct darr_st *darr = box;

	free(darr->ptr);
	free(darr);
}

static int bsearch__(const void *key, char *base, int num, int size, darr_cmp *cmp)
{
	int start, end, mid = -1;
	int sub;

	start = 0; end = num - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		sub = cmp(key, base + mid * size);
		if (sub == 0) {
			return mid;
		} else if (sub < 0) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return mid;
}

int darr_insert(DARR *box, const void *data)
{
	struct darr_st *darr = box;
	char *tmp;
	int ind;

	tmp = realloc(darr->ptr, darr->size * (darr->num + 1));
	if (tmp == NULL) {
		return -1;
	}
	darr->ptr = tmp;

	if (darr->num == 0 || darr->data_cmp == NULL) {
		memcpy(darr->ptr + darr->size * darr->num, data, darr->size);
	} else {
		ind = bsearch__(data, darr->ptr, darr->num, darr->size, darr->data_cmp);
		if (darr->data_cmp(data, darr->ptr + ind * darr->size) > 0) {
			ind++;
		}
		memmove(darr->ptr + (ind + 1) * darr->size, darr->ptr + ind * darr->size, (darr->num - ind) * darr->size);
		memcpy(darr->ptr + ind * darr->size, data, darr->size);
	}

	darr->num++;
	return 0;
}

void darr_travel(DARR *box, darr_op *op)
{
	struct darr_st *darr = box;
	int i;

	for (i = 0; i < darr->num; i++) {
		op(darr->ptr + i * darr->size);
	}
}

void darr_travel_adv(DARR *box, darr_op_adv *op, void *data)
{
	struct darr_st *darr = box;
	int i;

	for (i = 0; i < darr->num; i++) {
		op(darr->ptr + i * darr->size, data);
	}
}

void *darr_find(DARR *box, const void *key, darr_cmp *cmp)
{
	struct darr_st *darr = box;
	int i;

	if (darr->num == 0) {
		return NULL;
	}
	if (cmp != NULL) {
		for (i = 0; i < darr->num; i++) {
			if (cmp(key, darr->ptr + i * darr->size) == 0) {
				return darr->ptr + i * darr->size;
			}
		}
		return NULL;
	}

	return bsearch(key, darr->ptr, darr->num, darr->size, darr->key_cmp);
}

void darr_delet(DARR *box, const void *key, darr_cmp *cmp)
{
	struct darr_st *darr = box;
	int i;
	char *tmp;
	char *datap;

	if (darr->num == 0) {
		return;
	}
	if (cmp != NULL) {
		for (i = 0; i < darr->num; i++) {
			if (cmp(key, darr->ptr + i * darr->size) == 0) {
				memmove(darr->ptr + i * darr->size, darr->ptr + (i + 1) * darr->size, (darr->num - i - 1) * darr->size);
				darr->num--;
				darr->ptr = realloc(darr->ptr, darr->size * darr->num);
				break;
			}
		}
		return;
	}

	datap =  bsearch(key, darr->ptr, darr->num, darr->size, darr->key_cmp);
	if (datap == NULL) {
		return;
	}

	i = (datap - darr->ptr) / darr->size;
	memmove(darr->ptr + i * darr->size, darr->ptr + (i + 1) * darr->size, (darr->num - i - 1) * darr->size);
	darr->num--;
	darr->ptr = realloc(darr->ptr, darr->size * darr->num);
}
