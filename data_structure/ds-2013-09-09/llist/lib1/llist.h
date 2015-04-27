#ifndef HS_LLIST_H
#define HS_LLIST_H

#define LLIST_ADD_FORWARD   0
#define LLIST_ADD_BACKWARD  1

typedef void llist_op(void *);
typedef int llist_cmp(const void *, const void *);

struct llist_node_st {
	void *data;
	struct llist_node_st *prev;
	struct llist_node_st *next;
};

typedef struct {
	int size;
	struct llist_node_st head;
} LLIST;

LLIST *llist_creat(int size);

void llist_destroy(LLIST *);

int llist_add(LLIST *, const void *data, int dir);

void llist_delet(LLIST *, const void *key, llist_cmp *cmp);

void *llist_find(LLIST *, const void *key, llist_cmp *cmp);

void llist_travel(LLIST *, llist_op *op);

#if 0
/* homeworks */
llist_fetch();
#endif

#endif	/* HS_LLIST_H */
