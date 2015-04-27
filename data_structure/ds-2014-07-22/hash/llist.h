#ifndef HS_LLIST_H
#define HS_LLIST_H

typedef int llist_cmp(const void *, const void *);
typedef void llist_op(void *, void *priv);

struct llist_node_st {
	struct llist_node_st *next;
	struct llist_node_st *prev;
	char data[0];
};

typedef struct {
	struct llist_node_st head;
	int size;
	/* home works */
	int num;
} LLIST;

LLIST *llist_creat(int size);

void llist_destroy(LLIST *);

int llist_insert(LLIST *, const void *data);
/* home works */
/* llist_insert(LLIST *, const void *data, int dir); */

void llist_delet(LLIST *, const void *key, llist_cmp *cmp);

void *llist_find(LLIST *, const void *key, llist_cmp *cmp);

void llist_travel(LLIST *, llist_op *op, void *priv);

/* home works */

int llist_fetch(LLIST *, const void *key, llist_cmp *cmp, void *data);

int llist_get_num(LLIST *);

#if 0
llist_save();
llist_load();
#endif

#endif	/* HS_LLIST_H */
