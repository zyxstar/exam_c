#ifndef HS_DARR_H
#define HS_DARR_H

typedef int darr_cmp(const void *, const void *);
typedef void darr_op(void *);

typedef struct {
	char *arr;
	int size;
	int num;
	darr_cmp *key_cmp;
	darr_cmp *data_cmp;
} DARR;

DARR *darr_creat(int size);

DARR *darr_creat_sort(int size, darr_cmp *key_cmp, darr_cmp *data_cmp);

void darr_set_sort(DARR *, darr_cmp *key_cmp, darr_cmp *data_cmp);

void darr_destroy(DARR *);

int darr_insert(DARR *, const void *data);

void darr_delet(DARR *, const void *key, darr_cmp *cmp);

void *darr_search(DARR *, const void *key, darr_cmp *cmp);

void darr_travel(DARR *, darr_op *op);

#endif	/* HS_DARR_H */
