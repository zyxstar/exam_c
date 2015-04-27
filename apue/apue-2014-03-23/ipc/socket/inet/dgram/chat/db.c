#include <stdlib.h>

#include "db.h"

#if 0
struct db_data_st {
	uint32_t id;
	struct sockaddr_in addr;
	/* last_time */
	/* online */
};
typedef void DB;
#endif

struct db_node_st {
	struct db_data_st data;
	struct db_node_st *prev, *next;
};

DB *db_creat(void)
{
	struct db_node_st *head;

	head = malloc(sizeof(*head));
	/* if error */

	head->prev = head->next = head;

	return head;
}

void db_destroy(DB *box)
{
	struct db_node_st *ptr = box;
	struct db_node_st *cur, *save;

	for (cur = ptr->next; cur != ptr; cur = save) {
		save = cur->next;
		free(cur);
	}

	free(ptr);
}

int db_insert(DB *box, struct db_data_st *data)
{
	struct db_node_st *newnode;
	struct db_node_st *ptr = box;

	newnode = malloc(sizeof(*newnode));
	/* if error */

	newnode->data = *data;
	newnode->prev = ptr;
	newnode->next = ptr->next;
	newnode->prev->next = newnode;
	newnode->next->prev = newnode;

	return 0;
}

void db_delet(DB *box, uint32_t id)
{
	struct db_node_st *ptr = box;
	struct db_node_st *cur;

	for (cur = ptr->next; cur != ptr; cur = cur->next) {
		if (cur->data.id == id) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			return;
		}
	}
}

struct db_data_st *db_search(DB *box, uint32_t id)
{
	struct db_node_st *ptr = box;
	struct db_node_st *cur;

	for (cur = ptr->next; cur != ptr; cur = cur->next) {
		if (cur->data.id == id) {
			return &cur->data;
		}
	}

	return NULL;
}
