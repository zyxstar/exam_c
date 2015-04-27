#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "darr.h"
#include "debug.h"

//#define DEBUG

#if 0
typedef struct {
	char *arr;
	int num;
	int size;
} DARR;
#endif

DARR *darr_creat(int size)
{
	DARR *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->arr = NULL;
	new->num = 0;
	new->size = size;

	debug2("%s(): new = %p\n", __func__, new);

	return new;
}

void darr_destroy(DARR *ptr)
{
	free(ptr->arr);
	free(ptr);
}

int darr_insert(DARR *ptr, void *data)
{
	void *tmp;

	tmp = realloc(ptr->arr, ptr->size * (ptr->num + 1));
	if (tmp == NULL) {
		return -1;
	}
	ptr->arr = tmp;

	memcpy(ptr->arr + ptr->size * ptr->num, data, ptr->size);
	ptr->num++;

	return 0;
}

void darr_travel(DARR *ptr, darr_op *op)
{
	int i;

	for (i = 0; i < ptr->num; i++) {
		op(ptr->arr + i * ptr->size);
	}
}

void *darr_find(DARR *ptr, void *key, darr_cmp *cmp)
{
	int i;

	for (i = 0; i < ptr->num; i++) {
                if (cmp(key, ptr->arr + i * ptr->size) == 0) {
			return ptr->arr + i * ptr->size;
		}
	}
	return NULL;
}

void darr_delet(DARR *ptr, void *key, darr_cmp *cmp)
{
	int i;

	for (i = 0; i < ptr->num; i++) {
                if (cmp(key, ptr->arr + i * ptr->size) == 0) {
			memmove(ptr->arr + i * ptr->size, ptr->arr + (i + 1) * ptr->size, ptr->size * (ptr->num - i - 1));
			ptr->num--;
			ptr->arr = realloc(ptr->arr, ptr->num * ptr->size);
			return;
		}
	}
}
