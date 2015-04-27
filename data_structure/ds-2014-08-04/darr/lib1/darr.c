#include <stdlib.h>
#include <string.h>

#include "darr.h"

#if 0
typedef void darr_op(void *);
typedef struct darr_st {
	int size;
	int num;
	char *ptr;
} DARR;
#endif

DARR *darr_creat(int size)
{
	DARR *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->num = 0;
	new->ptr = NULL;

	return new;
}

void darr_destroy(DARR *darr)
{
	free(darr->ptr);
	free(darr);
}

int darr_insert(DARR *darr, const void *data)
{
	char *tmp;

	tmp = malloc(darr->size * (darr->num + 1));
	if (tmp == NULL) {
		return -1;
	}

	memcpy(tmp, darr->ptr, darr->size * darr->num);
	memcpy(tmp + darr->size * darr->num, data, darr->size);
	darr->num++;

	free(darr->ptr);
	darr->ptr = tmp;

	return 0;
}

void darr_travel(DARR *darr, darr_op *op)
{
	int i;

	for (i = 0; i < darr->num; i++) {
		op(darr->ptr + i * darr->size);
	}
}

void *darr_find(DARR *darr, const void *key, darr_cmp *cmp)
{
	int i;

	for (i = 0; i < darr->num; i++) {
		if (cmp(key, darr->ptr + i * darr->size) == 0) {
			return darr->ptr + i * darr->size;
		}
	}

	return NULL;
}

void darr_delet(DARR *darr, const void *key, darr_cmp *cmp)
{
	int i;
	char *tmp;

	for (i = 0; i < darr->num; i++) {
		if (cmp(key, darr->ptr + i * darr->size) == 0) {
			tmp = malloc(darr->size * (darr->num - 1));
			/* if error */

			memcpy(tmp, darr->ptr, i * darr->size);
			memcpy(tmp + i * darr->size, darr->ptr + (i + 1) * darr->size, (darr->num - i - 1) * darr->size);
			darr->num--;
			free(darr->ptr);
			darr->ptr = tmp;
			return;
		}
	}
}
