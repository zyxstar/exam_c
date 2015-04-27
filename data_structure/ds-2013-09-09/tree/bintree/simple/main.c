#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NAMESIZE 32

struct stu {
	int id;
	char name[NAMESIZE];
};

struct node_st {
	struct stu data;
	struct node_st *l, *r;
};

static struct node_st *tree = NULL;

static void print_stu(struct stu *data)
{
	printf("%d %s\n", data->id, data->name);
}

static struct node_st *find_min(struct node_st *root)
{
	if (root->l == NULL) {
		return root;
	}
	return find_min(root->l);
}

static struct node_st *find_max(struct node_st *root)
{
	if (root->r == NULL) {
		return root;
	}
	return find_max(root->r);
}

int insert(struct node_st **root, struct stu *data)
{
	struct node_st *node;

	if (*root == NULL) {
		node = malloc(sizeof(*node));
		/* if error */
		node->data = *data;
		node->l = node->r = NULL;
		*root = node;
		return;
	}

	if (data->id < (*root)->data.id) {
		return insert(&(*root)->l, data);
	}
	return insert(&(*root)->r, data);
}

struct stu *find(struct node_st *root, int id)
{
	if (root == NULL) {
		return NULL;
	}

	if (id == root->data.id) {
		return &root->data;
	} else if (id < root->data.id) {
		return find(root->l, id);
	} else {
		return find(root->r, id);
	}
}

void travel(struct node_st *root)
{
	if (root == NULL) {
		return;
	}

	travel(root->l);
	print_stu(&root->data);
	travel(root->r);
}

void travel_broad(struct node_st *root)
{
	LLIST *queue;
	struct node_st **node;

	queue = Creatqueue(sizeof(struct node_st *));
	/* if error */

	Inqueue(queue, &root);
	/* if error */
	while (1) {
		node = Outqueue(queue);
		if (node == NULL) {
			break;
		}

		print_stu(&(*node)->data);
		if ((*node)->l != NULL) {
			Inqueue(queue, &(*node)->l);
		}
		if ((*node)->r != NULL) {
			Inqueue(queue, &(*node)->r);
		}
		free(node);
	}

	Destory(queue);
}

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
	print_stu(&root->data);

	draw__(root->l, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static void delete__(struct node_st **root)
{
	struct node_st *cur = *root;
	struct node_st *left = (*root)->l;
	struct node_st *right = (*root)->r;

	if (left == NULL) {
		*root = right;
		free(cur);
		return;
	}

	find_max(left)->r = right;
	*root = left;
	free(cur);
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
	} else {
		delete(&(*root)->r, id);
	}
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
	struct node_st *cur = *root;
	struct node_st *right = (*root)->r;

	cur->r = NULL;
	find_min(right)->l = cur;
	*root = right;

	draw(tree);
	getchar();
}

static void turn_right(struct node_st **root)
{
	struct node_st *cur = *root;
	struct node_st *left = (*root)->l;

	cur->l = NULL;
	find_max(left)->r = cur;
	*root = left;

	draw(tree);
	getchar();
}

void balance(struct node_st **root)
{
	int ret;

	if (*root == NULL) {
		return;
	}

	while (1) {
		ret = get_num((*root)->l) - get_num((*root)->r);
		if (ret >= -1 && ret <= 1) {
			break;
		}
		if (ret > 1) {
			turn_right(root);
		} else {
			turn_left(root);
		}
	}

	balance(&(*root)->l);
	balance(&(*root)->r);
}

int main(void)
{
	int arr[] = {3,4,5,1,6,2,8,9,7};
	int i;
	struct stu tmp, *p;

	for (i = 0; i < sizeof(arr)/ sizeof(*arr); i++) {
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		insert(&tree, &tmp);
	}

	draw(tree);
	printf("\n");
	travel_broad(tree);

#if 0
	balance(&tree);
	printf("\n");
	draw(tree);
	delete(&tree, 5);
	draw(tree);
	travel(tree);
	printf("\n");
	p = find(tree, 21);
	if (p == NULL) {
		printf("Can not find.\n");
	} else {
		print_stu(p);
	}
#endif
	return 0;
}
