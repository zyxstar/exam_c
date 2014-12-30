#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#if 0
#define LLIST_FORWARD      1
#define LLIST_BACKWARD     2
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
#endif

LLIST *llist_creat(int size)
{
      LLIST *new;

      new = malloc(sizeof(*new));
      if (new == NULL) {
	    return NULL;
      }

      new->size = size;
      new->head.prev = new->head.next = &new->head;

      return new;
}

void llist_destroy(LLIST *ptr)
{
      struct llist_node_st *cur, *save;

      for (cur = ptr->head.next; cur != &ptr->head; cur = save) {
	    save = cur->next;
	    free(cur);
      }
      free(ptr);
}

int llist_insert(LLIST *ptr, const void *data, int mode)
{
      struct llist_node_st *newnode;

      newnode = malloc(sizeof(*newnode) + ptr->size);
      if (newnode == NULL) {
	    return -1;
      }
      memcpy(newnode->data, data, ptr->size);

      if (mode == LLIST_FORWARD) {
	    newnode->next = ptr->head.next;
	    newnode->prev = &ptr->head;
      } else if (mode == LLIST_BACKWARD) {
	    newnode->next = &ptr->head;
	    newnode->prev = ptr->head.prev;
      }

      newnode->next->prev = newnode;
      newnode->prev->next = newnode;

      return 0;
}

static struct llist_node_st *find__(LLIST *ptr, const void *key, llist_cmp *cmp)
{
      struct llist_node_st *cur;

      for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
	    if (!cmp(key, cur->data)) {
		  break;
	    }
      }

      return cur;
}

void llist_delet(LLIST *ptr, const void *key, llist_cmp *cmp)
{
      struct llist_node_st *node;

      node = find__(ptr, key, cmp);
      if (node == &ptr->head) {
            return;
      }

      node->next->prev = node->prev;
      node->prev->next = node->next;

      free(node);
}

void *llist_find(LLIST *ptr, const void *key, llist_cmp *cmp)
{
      struct llist_node_st *node;

      node = find__(ptr, key, cmp);
      if (node == &ptr->head) {
	    return NULL;
      }

      return node->data;
}

void llist_travel(LLIST *ptr, llist_op *op)
{
      struct llist_node_st *cur;

      for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
	    op(cur->data);
      }
}

int llist_fetch(LLIST *ptr, void *data, const void *key, llist_cmp *cmp)
{
      struct llist_node_st *node;

      node = find__(ptr, key, cmp);
      if (node == &ptr->head) {
	    return -1;
      }

      memcpy(data, node->data, ptr->size);
      node->prev->next = node->next;
      node->next->prev = node->prev;
      free(node);

      return 0;
}

int llist_getnum(LLIST *ptr)
{
      int i;
      struct llist_node_st *cur;

      for (i = 0, cur = ptr->head.next; \
	   cur != &ptr->head; \
	   cur = cur->next, i++)
	    ;

      return i;
}

#if 1
/* homeworks */
int llist_save(LLIST *ptr, const char *path)
{
      FILE *fp;
      struct llist_node_st *cur;
      int num;
      long offset_self, offset_num, offset_data;
      int ret;
      int version = VERSION;

      fp = fopen(path, "w");
      if (fp == NULL) {
	    return -1;
      }

      fwrite(&version, sizeof(version), 1, fp);
      /* if error */
      offset_self = ftell(fp);
      /* if error */
      fseek(fp, sizeof(offset_data), SEEK_CUR);
      /* if error */
      fwrite(&ptr->size, sizeof(ptr->size), 1, fp); /* fix me */
      /* if error */

      offset_num = ftell(fp);
      /* if error */
      fseek(fp, sizeof(num), SEEK_CUR);
      /* if error */

      offset_data = ftell(fp);
      /* if error */
      for (cur = ptr->head.next, num = 0; cur != &ptr->head; cur = cur->next, num++) {
	    ret = fwrite(cur->data, ptr->size, 1, fp);
	    if (ret == 0) {
		  return -1;
	    }
      }
      fseek(fp, offset_self, SEEK_SET);
      /* if error */
      fwrite(&offset_data, sizeof(offset_data), 1, fp);
      /* if error */

      fseek(fp, offset_num, SEEK_SET);
      /* if error */
      fwrite(&num, sizeof(num), 1, fp);
      /* if error */

      fclose(fp);
      return 0;
}

LLIST *llist_load(const char *path)
{
      LLIST *new;
      struct llist_node_st *newnode;
      FILE *fp;
      int num;
      int i;
      long offset;
      int version;

      fp = fopen(path, "r");
      if (fp == NULL) {
	    return NULL;
      }

      new = malloc(sizeof(*new));
      if (new == NULL) {
	    fclose(fp);
	    return NULL;
      }

      new->head.prev = new->head.next = &new->head;

      fread(&version, sizeof(version), 1, fp);
      /* if error */
      /* if version */

      fread(&offset, sizeof(offset), 1, fp);
      /* if error */

      fread(&new->size, sizeof(new->size), 1, fp);
      /* if error */
      fread(&num, sizeof(num), 1, fp);
      /* if error */

      fseek(fp, offset, SEEK_SET);
      /* if error */
      for (i = 0; i < num; i++) {
	    newnode = malloc(sizeof(*newnode) + new->size);
	    /* if error */
	    fread(newnode->data, new->size, 1, fp);
	    /* if error */

	    newnode->prev = new->head.prev;
	    newnode->next = &new->head;
	    newnode->prev->next = newnode;
	    newnode->next->prev = newnode;
      }

      fclose(fp);
      return new;
}

#endif
