#ifndef HS_LLIST_H
#define HS_LLIST_H

typedef int llist_cmp(const void *, const void *);
typedef void llist_op(void *, void *);

#define DIR_FRONT 0
#define DIR_BACK  1

struct node_st {
	void *data;
	struct node_st *prev;
	struct node_st *next;
};

typedef struct {
	struct node_st head;
	int size;
} LLIST;

LLIST *llist_creat(int size);

void llist_destroy(LLIST *);

int llist_insert(LLIST *, const void *data, int dir);

void llist_delet(LLIST *, const void *key, llist_cmp *cmp);

void *llist_search(LLIST *, const void *key, llist_cmp *cmp);

int llist_fetch(LLIST *, void *data, const void *key, llist_cmp *cmp);

void llist_travel(LLIST *, llist_op *op, void *arg);

/* homeworks */
llist_save();
llist_load();

#endif	/* HS_LLIST_H */
