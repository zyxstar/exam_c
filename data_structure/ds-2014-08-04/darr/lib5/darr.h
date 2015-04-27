#ifndef HS_DARR_H
#define HS_DARR_H

typedef void darr_op(void *);
typedef void darr_op_adv(void *, void *);
typedef int darr_cmp(const void *, const void *);

typedef void DARR;

DARR *darr_creat(int size);

DARR *darr_creat_sort(int size, darr_cmp *key_cmp, darr_cmp *data_cmp);

void darr_sort(DARR *box, darr_cmp *key_cmp, darr_cmp *data_cmp);

void darr_destroy(DARR *);

int darr_insert(DARR *, const void *data);

void darr_travel(DARR *, darr_op *op);

void darr_travel_adv(DARR *, darr_op_adv *op, void *data);

void *darr_find(DARR *, const void *key, darr_cmp *cmp);

void darr_delet(DARR *, const void *key, darr_cmp *cmp);

#endif	/* HS_DARR_H */
