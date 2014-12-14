#ifndef _LIST_H__
#define _LIST_H__

struct list_node;
typedef int list_t;
typedef struct list_node *LIST;
typedef struct list_node *PtrNode;
typedef struct list_node *Position;

LIST list_create();
int list_is_empty(LIST l);
int list_is_last(LIST l, Position p);
int list_insert(LIST l, const list_t *data, Position prev);
int list_insert_head(LIST l, const list_t *data);
int list_insert_tail(LIST l, const list_t *data);
PtrNode list_find(LIST l, const list_t *key);
PtrNode list_find_prev(LIST l,const list_t *key);
int list_delete(LIST l, const list_t *key);
void list_display(LIST l);
void list_dispose(LIST l);

struct list_node {
	list_t data;
	struct list_node *next;
};

#endif
