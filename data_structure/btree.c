#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define NAMESIZE 32

struct score {
      int id;
      char name[NAMESIZE];
      int math;
};

struct node_st {
      struct score data;
      struct node_st *l, *r;
};

struct node_st *tree = NULL;

void print_s(void *data)
{
      struct score *d = data;
      printf("%d %s %d\n", d->id, d->name, d->math);
}

int id_cmp(const void *key, const void *record)
{
      const int *id = key;
      const struct score *r = record;

      return *id - r->id;
}

int name_cmp(const void *key, const void *record)
{
      const char *k = key;
      const struct score *r = record;

      return strcmp(k, r->name);
}

void rand_name(char *buf, int n)
{
      int len, c;
      int i;
      char arr[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

      len = (unsigned)rand() % (n - 2) + 1;
      for (i = 0; i < len; i++) {
	    c = arr[(unsigned)rand() % (sizeof(arr) - 1)];
	    buf[i] = c;
      }
      buf[i] = '\0';
}

int insert(struct node_st **root, struct score *data)
{
      struct node_st *newnode;

      if (*root == NULL) {
	    newnode = malloc(sizeof(*newnode));
	    /* if error */

	    newnode->data = *data;
	    newnode->l = newnode->r = NULL;

	    *root = newnode;
	    return 0;
      }

      if (data->id <= (*root)->data.id) {
	    return insert(&(*root)->l, data);
      } else {
	    return insert(&(*root)->r, data);
      }
}

static struct score *find(struct node_st *root, int id)
{
      if (root == NULL) {
	    return NULL;
      }
      if (id == root->data.id) {
	    return &root->data;
      }
      if (id < root->data.id) {
	    return find(root->l, id);
      }
      return find(root->r, id);
}

#if 1
void travel(struct node_st *root)
{
      if (root == NULL) {
	    return;
      }

      travel(root->l);
      print_s(&root->data);
      travel(root->r);
}
#endif
#if 0
void travel(struct node_st *root)
{
      QUEUE *q;
      struct node_st *cur;
      int ret;

      if (root == NULL) {
	    return;
      }

      q = queue_creat(sizeof(struct node_st *));
      /* if error */

      queue_enq(q, &root);
      /* if error */
      while (1) {
	    ret = queue_deq(q, &cur);
	    if (ret == -1) {
		  break;
	    }

	    print_s(&cur->data);

	    if (cur->l != NULL) {
		  queue_enq(q, &cur->l);
	    }
	    if (cur->r != NULL) {
		  queue_enq(q, &cur->r);
	    }
      }

      queue_destroy(q);
}
#endif

static void draw__(struct node_st *root, int level)
{
      int i;

      if (root == NULL) {
	    return;
      }

      draw__(root->r, level + 1);

      for (i = 0; i < level; i++) {
	    printf("      ");
      }
      print_s(&root->data);

      draw__(root->l, level + 1);
}

void draw(struct node_st *root)
{
      draw__(root, 0);
      getchar();
}

static struct node_st **find__(struct node_st **root, int id)
{
      if (*root == NULL) {
	    return NULL;
      }
      if (id == (*root)->data.id) {
	    return root;
      }
      if (id < (*root)->data.id) {
	    return find__(&(*root)->l, id);
      }
      return find__(&(*root)->r, id);
}

static struct node_st *find_max(struct node_st *root)
{
      while (root->r != NULL) {
	    root = root->r;
      }

      return root;
}

static struct node_st *find_min(struct node_st *root)
{
      while (root->l != NULL) {
	    root = root->l;
      }

      return root;
}

void delete(struct node_st **root, int id)
{
      struct node_st **node, *save;

      node = find__(root, id);
      if (node == NULL) {
	    return;
      }

      save = *node;
      if (save->l == NULL) {
	    *node = save->r;
      } else {
	    *node = save->l;
	    find_max(save->l)->r = save->r;
      }
      free(save);
}

static int getnum(struct node_st *root)
{
      if (root == NULL) {
	    return 0;
      }

      return getnum(root->l) + 1 + getnum(root->r);
}

static void turn_left(struct node_st **root)
{
      struct node_st *cur, *right;

      cur = *root; right = cur->r;
      *root = right;
      cur->r = NULL;

      find_min(right)->l = cur;

      //draw(tree);
}

static void turn_right(struct node_st **root)
{
      struct node_st *cur, *left;

      cur = *root; left = cur->l;
      *root = left;
      cur->l = NULL;

      find_max(left)->r = cur;

      //draw(tree);
}

void balance(struct node_st **root)
{
      int sub;

      if (*root == NULL) {
	    return;
      }

      while (1) {
	    sub = getnum((*root)->l) - getnum((*root)->r);

	    if (sub >= -1 && sub <= 1) {
		  break;
	    }
	    if (sub < -1) {
		  turn_left(root);
	    } else {
		  turn_right(root);
	    }
      }

      balance(&(*root)->l);
      balance(&(*root)->r);
}

int main(void)
{
      struct score tmp, *datap;
      int i;
      //int arr[] = {5,3,1,7,4,9,8,2};
      int arr[] = {1,2,5,4,3,4,8,5,6,7,9,};

      for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
	    tmp.id = arr[i];
	    tmp.math = 100 - arr[i];
	    snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
	    //rand_name(tmp.name, NAMESIZE);

	    insert(&tree, &tmp);
      }
#if 0
      datap = find(tree, 6);
      if (datap == NULL) {
	    printf("Can not find.\n");
      } else {
	    print_s(datap);
      }
#endif
      draw(tree);
      travel(tree);
      //delete(&tree, 3);
      //draw(tree);

      getchar();
      balance(&tree);
      draw(tree);
      travel(tree);

      return 0;
}
