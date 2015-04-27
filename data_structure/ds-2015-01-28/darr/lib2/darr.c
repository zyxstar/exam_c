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

	return new;
}

void darr_destroy(DARR *ptr)
{
	free(ptr->arr);
	free(ptr);
}

int darr_insert(DARR *ptr, const void *data)
{
	char *tmp;

	tmp = realloc(ptr->arr, ptr->size * (ptr->num + 1));
	if (tmp == NULL) {
		return -1;
	}
	ptr->arr = tmp;

	memcpy(ptr->arr + ptr->size * ptr->num, data, ptr->size);
	ptr->num++;

	return 0;
}

void darr_delet(DARR *ptr, const void *key, darr_cmp *cmp)
{
	int i;
	char *tmp;

        for (i = 0; i < ptr->num; i++) {
		if (cmp(key, ptr->arr + i * ptr->size) == 0) {
			break;
		}
        }

	if (i == ptr->num) {
		return;
	}

	memmove(ptr->arr + i * ptr->size, ptr->arr + (i + 1) * ptr->size, (ptr->num - i - 1) * ptr->size);
	ptr->num--;

	ptr->arr = realloc(ptr->arr, ptr->size * ptr->num);
}

void *darr_search(DARR *ptr, const void *key, darr_cmp *cmp)
{
	int i;

        for (i = 0; i < ptr->num; i++) {
		if (cmp(key, ptr->arr + i * ptr->size) == 0) {
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
