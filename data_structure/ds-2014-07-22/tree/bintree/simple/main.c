#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
};

struct node_st {
	struct score data;
	struct node_st *l, *r;
};

static struct node_st *tree = NULL;

#if 0
int insert(struct node_st **root, struct score *data)
{
	struct node_st *node;

	if (*root == NULL) {
		node = malloc(sizeof(*node));
		/* if error */
		node->data = *data;
		node->l = node->r = NULL;
		*root = node;
		return 0;
	}

	if (data->id <= (*root)->data.id) {
		return insert(&(*root)->l, data);
	}
	return insert(&(*root)->r, data);
}
#else
int insert(struct node_st **root, struct score *data)
{
	struct node_st *node;

	node = malloc(sizeof(*node));
	/* if error */
	node->data = *data;
	node->l = node->r = NULL;

	while (*root != NULL) {
		if (data->id <= (*root)->data.id) {
			root = &(*root)->l;
		} else {
			root = &(*root)->r;
		}
	}

	*root = node;
	return 0;
}
#endif

#if 0
struct score *find(struct node_st *root, int id)
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
#else
struct score *find(struct node_st *root, int id)
{
	while (root != NULL) {
		if (id == root->data.id) {
			return &root->data;
		}
		if (id < root->data.id) {
			root = root->l;
		} else {
			root = root->r;
		}
	}

	return NULL;
}
#endif

#if 0
void travel(struct node_st *root)
{
	if (root == NULL) {
		return;
	}

	travel(root->l);
	travel(root->r);
	printf("%d %s\n", root->data.id, root->data.name);
}
#else
int travel(struct node_st *root)
{
	QUEUE *q;
	struct node_st *cur;
	int ret;

	q = queue_create(sizeof(struct node_st *));
	/* if error */

	if (root == NULL) {
		return 0;
	}
	queue_enq(q, &root);
	/* if error */

	while (1) {
		ret = queue_deq(q, &cur);
		if (ret == -1) {
			break;
		}

		printf("%d %s\n", cur->data.id, cur->data.name);
		if (cur->l != NULL) {
			queue_enq(q, &cur->l);
			/* if error */
		}
		if (cur->r != NULL) {
			queue_enq(q, &cur->r);
			/* if error */
		}
	}

	queue_destroy(q);
	return 0;
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
	printf("%d %s\n", root->data.id, root->data.name);
	draw__(root->l, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static struct node_st *find_max(struct node_st *root)
{
	if (root->r == NULL) {
		return root;
	}
	return find_max(root->r);
}

static struct node_st *find_min(struct node_st *root)
{
	if (root->l == NULL) {
		return root;
	}
	return find_min(root->l);
}

static void delete__(struct node_st **root)
{
	struct node_st *node = *root;
	struct node_st *left, *right;

	left = node->l; right = node->r;

	if (node->l == NULL) {
		*root = right;
		free(node);
		return;
	}

	find_max(left)->r = right;
	*root = left;
	free(node);
}

void delete(struct node_st **root, int id)
{
	if (*root == NULL) {
		return;
	}

	if (id == (*root)->data.id) {
		delete__(root);
		return;
	}

	if (id < (*root)->data.id) {
		delete(&(*root)->l, id);
		return;
	}

	delete(&(*root)->r, id);
}

static int get_num(struct node_st *root)
{
	if (root == NULL) {
		return 0;
	}

	return get_num(root->l) + 1 + get_num(root->r);
}

static void turn_left(struct node_st **root)
{
	struct node_st *cur, *right;

	cur = *root; right = cur->r;

	*root = right;
	cur->r = NULL;
	find_min(right)->l = cur;

	//draw(tree);
	//getchar();
}

static void turn_right(struct node_st **root)
{
	struct node_st *cur, *left;

	cur = *root; left = cur->l;

	*root = left;
	cur->l = NULL;
	find_max(left)->r = cur;

	//draw(tree);
	//getchar();
}

void balance(struct node_st **root)
{
	int sub;

	if (*root == NULL) {
		return;
	}

	while (1) {
		sub = get_num((*root)->l) - get_num((*root)->r);
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

void destroy(struct node_st *root)
{
	if (root == NULL) {
		return;
	}

	destroy(root->l);
	destroy(root->r);
	free(root);
}

int main(void)
{
	struct score tmp, *datap;
	int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
	int i;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);

		insert(&tree, &tmp);
	}

	//draw(tree);
	//getchar();
#if 1
	balance(&tree);
	draw(tree);
	printf("\n");
	travel(tree);
#else
	datap = find(tree, 60);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s\n", datap->id, datap->name);
	}
	delete(&tree, 5);
	printf("\n");	travel(tree);
	datap = find(tree, 7);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s\n", datap->id, datap->name);
	}
#endif

	destroy(tree);

	return 0;
}
