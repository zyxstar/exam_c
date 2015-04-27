#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

LLIST *llist_creat(int size)
{
	LLIST *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->head.next = new->head.prev = &new->head;

	return new;
}

void llist_destroy(LLIST *ptr)
{
	struct llist_node_st *cur, *next;

	for (cur = ptr->head.next; cur != &ptr->head; cur = next) {
		next = cur->next;
		free(cur);
	}
	free(ptr);
}

int llist_insert(LLIST *ptr, const void *data, int dir)
{
	struct llist_node_st *node;

	node = malloc(sizeof(*node) + ptr->size);
	if (node == NULL) {
		return -1;
	}

	memcpy(node->data, data, ptr->size);
	if (dir == DIR_FRONT) {
		node->next = ptr->head.next;
		node->prev = &ptr->head;
	} else {
		node->next = &ptr->head;
		node->prev = ptr->head.prev;
	}
	node->next->prev = node;
	node->prev->next = node;

	return 0;
}

void llist_delet(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;

			free(cur);
			return;
		}
        }
}

void *llist_search(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

        for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			return cur->data;
		}
        }
	return NULL;
}

int llist_fetch(LLIST *ptr, void *data, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			memcpy(data, cur->data, ptr->size);

			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;

			free(cur);
			return 0;
		}
        }

	return -1;
}

void llist_travel(LLIST *ptr, llist_op *op, void *arg)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		op(cur->data, arg);
	}
}

struct __attribute__ ((__packed__)) file_status {
	char magic_num[2];
	uint16_t version;
	uint16_t offset;
	uint32_t size;
};

int llist_save(LLIST *ptr, const char *path)
{
	FILE *fp;
	struct llist_node_st *cur;
	struct file_status status = {
		.magic_num = {'l', 's'},
		.version = 1,
		.offset = sizeof(struct file_status),
	};

	fp = fopen(path, "w");
	if (fp == NULL) {
		return -1;
	}

	status.size = ptr->size;
	fwrite(&status, sizeof(struct file_status), 1, fp);
	/* if error */

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		fwrite(cur->data, ptr->size, 1, fp);
		/* if error */
	}

	fclose(fp);
	return 0;
}

LLIST *llist_load(const char *path)
{
	LLIST *new;
	struct file_status status;
	FILE *fp;
	struct llist_node_st *newnode;
	void *data;
	int ret;

	fp = fopen(path, "r");
	if (fp == NULL) {
		goto fopen_err;
	}

	new = malloc(sizeof(*new));
	if (new == NULL) {
		goto malloc_list_err;
	}

	ret = fread(&status, sizeof(status), 1, fp);
	if (ret < 1) {
		goto read_status_err;
	}

	if (strncmp(status.magic_num, "ls", 2) != 0) {
		goto magic_num_err;
	}

	data = malloc(status.size);
	if (data == NULL) {
		goto malloc_data_buf_err;
	}

	new->size = status.size;
	new->head.next = new->head.prev = &new->head;

	while (1) {
		ret = fread(data, status.size, 1, fp);
		if (ret == 0) {
			break;
		}
		if (ret < 1) {
			goto read_data_err;
		}

		newnode = malloc(sizeof(*newnode) + status.size);
		if (newnode == NULL) {
			goto malloc_newnode_err;
		}

		memcpy(newnode->data, data, status.size);
		newnode->next = &new->head;
		newnode->prev = new->head.prev;
		newnode->next->prev = newnode;
		newnode->prev->next = newnode;
	}

	free(data);
	fclose(fp);

	return new;



malloc_newnode_err:
read_data_err:
	llist_destroy(new);
	free(data);
	fclose(fp);
	return NULL;


	free(data);
malloc_data_buf_err:
magic_num_err:
read_status_err:
	free(new);
malloc_list_err:
	fclose(fp);
fopen_err:
	return NULL;
}
