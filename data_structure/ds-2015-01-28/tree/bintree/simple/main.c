#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <queue.h>
#include "queue.h"

#define NAMESIZE  32

struct score {
	int id;
	char name[NAMESIZE];
};

struct node_st {
	struct score data;
	struct node_st *left, *right;
};

static struct node_st *tree = NULL;

#if 0
int insert(struct node_st **root, struct score *data)
{
	struct node_st *newnode;

	if (*root == NULL) {
		newnode = malloc(sizeof(*newnode));
		if (newnode == NULL) {
			return -1;
		}
		newnode->data = *data;
		newnode->left = newnode->right = NULL;
		*root = newnode;
		return 0;
	}

	if (data->id <= (*root)->data.id) {
		return insert(&(*root)->left, data);
	}
	return insert(&(*root)->right, data);
}
#else
int insert(struct node_st **root, struct score *data)
{
	struct node_st *newnode;
	struct node_st **p;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		return -1;
	}
	newnode->data = *data;
	newnode->left = newnode->right = NULL;

	p = root;
	while (*p != NULL) {
		if (data->id <= (*p)->data.id) {
			p = &(*p)->left;
		} else {
			p = &(*p)->right;
		}
	}

	*p = newnode;

	return 0;
}
#endif

#if 0
struct score *search(struct node_st *root, int id)
{
	if (root == NULL) {
		return NULL;
	}
	if (id == root->data.id) {
		return &root->data;
	}
	if (id < root->data.id) {
		return search(root->left, id);
	}
	return search(root->right, id);
}
#else
struct score *search(struct node_st *root, int id)
{
	struct node_st *cur;

	cur = root;
	while (cur != NULL) {
		if (id == cur->data.id) {
			return &cur->data;
		}
		if (id < cur->data.id) {
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}

	return NULL;
}
#endif

void travel(struct node_st *root)
{
	if (root == NULL) {
		return;
	}

	printf("%d %s\n", root->data.id, root->data.name);
	travel(root->left);
	travel(root->right);
}

void travel_broad(struct node_st *root)
{
	QUEUE *q;
	struct node_st *cur;
	int ret;

	q = queue_creat(sizeof(struct node_st *));
	/* if error */

	queue_enq(q, &root);
	while (1) {
		ret = queue_deq(q, &cur);
		if (ret == -1) {
			break;
		}

		printf("%d, %s\n", cur->data.id, cur->data.name);
		if (cur->left != NULL) {
			queue_enq(q, &cur->left);
		}
		if (cur->right != NULL) {
			queue_enq(q, &cur->right);
		}
	}

	queue_destroy(q);
}

static void draw__(struct node_st *root, int level)
{
	int i;

	if (root == NULL) {
		return;
	}

	draw__(root->right, level + 1);
	for (i = 0; i < level; i++) {
		printf("      ");
	}
	printf("%d %s\n", root->data.id, root->data.name);
	draw__(root->left, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static struct node_st *find_max(struct node_st *root)
{
	if (root->right == NULL) {
		return root;
	}
	return find_max(root->right);
}

static struct node_st *find_min(struct node_st *root)
{
	if (root->left == NULL) {
		return root;
	}
	return find_min(root->left);
}

static void delete__(struct node_st **root)
{
	struct node_st *cur, *l, *r;

	cur = *root; l = cur->left; r = cur->right;

	if (l == NULL) {
		*root = r;
		free(cur);
		return;
	}

	find_max(l)->right = r;
	free(cur);
	*root = l;
	return;
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
		delete(&(*root)->left, id);
	} else {
		delete(&(*root)->right, id);
	}
}

static int getnum(struct node_st *root)
{
	if (root == NULL) {
		return 0;
	}

	return getnum(root->left) + 1 + getnum(root->right);
}

static void turn_left(struct node_st **root)
{
	struct node_st *cur, *l, *r;

	cur = *root; l = cur->left; r = cur->right;

	*root = r;
	cur->right = NULL;
	find_min(r)->left = cur;

	//draw(tree);
	//getchar();
}

static void turn_right(struct node_st **root)
{
	struct node_st *cur, *l, *r;

	cur = *root; l = cur->left; r = cur->right;

	*root = l;
	cur->left = NULL;
	find_max(l)->right = cur;

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
		sub = getnum((*root)->left) - getnum((*root)->right);
		if (sub >= -1 && sub <= 1) {
			break;
		}

		if (sub < -1) {
			turn_left(root);
		} else {
			turn_right(root);
		}
	}

	balance(&(*root)->left);
	balance(&(*root)->right);
}

int main(void)
{
	int id[] = {1,2,3,4,5,6,7,8,9};
	int i;
	struct score tmp, *data;

	for (i = 0; i < sizeof(id) / sizeof(*id); i++) {
		tmp.id = id[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", id[i]);

		insert(&tree, &tmp);
	}

	balance(&tree);
	draw(tree);
	travel_broad(tree);
#if 0
	getchar();

	//printf("\n");
	delete(&tree, 10);
	draw(tree);

	travel(tree);
	data = search(tree, 2);
	if (data == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d, %s\n", data->id, data->name);
	}
#endif
	return 0;
}
