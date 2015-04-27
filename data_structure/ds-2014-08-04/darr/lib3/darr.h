#ifndef HS_DARR_H
#define HS_DARR_H

typedef void darr_op(void *);
typedef int darr_cmp(const void *, const void *);

typedef void DARR;

DARR *darr_creat(int size);

void darr_destroy(DARR *);

int darr_insert(DARR *, const void *data);

void darr_travel(DARR *, darr_op *op);

void *darr_find(DARR *, const void *key, darr_cmp *cmp);

void darr_delet(DARR *, const void *key, darr_cmp *cmp);

#endif	/* HS_DARR_H */
