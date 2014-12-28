#ifndef HS_LLIST_H
#define HS_LLIST_H

#define LLIST_FORWARD      1
#define LLIST_BACKWARD     2

#define VERSION 1

struct llist_node_st {
      struct llist_node_st *prev;
      struct llist_node_st *next;
      char data[0];
};

typedef struct {
      int size;
      struct llist_node_st head;
} LLIST;

typedef int llist_cmp(const void *, const void *);
typedef void llist_op(void *);

LLIST *llist_creat(int size);

void llist_destroy(LLIST *);

int llist_insert(LLIST *, const void *data, int mode);

void llist_delet(LLIST *, const void *key, llist_cmp *);

void *llist_find(LLIST *, const void *key, llist_cmp *);

void llist_travel(LLIST *, llist_op *);

int llist_fetch(LLIST *, void *data, const void *key, llist_cmp *);

int llist_getnum(LLIST *);

#if 1
/* homeworks */
int llist_save(LLIST *, const char *path);

LLIST *llist_load(const char *path);
#endif

#endif
