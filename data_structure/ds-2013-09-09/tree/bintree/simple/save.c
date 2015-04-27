#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NAMESIZE 32

struct node_st {
	char data;
	struct node_st *l, *r;
};

int insert(struct node_st **root, int data)
{
	struct node_st *node;

	if (*root == NULL) {
		node = malloc(sizeof(*node));
		/* if error */
		node->data = data;
		node->l = node->r = NULL;
		*root = node;
		return;
	}

	if (data < (*root)->data) {
		return insert(&(*root)->l, data);
	}
	return insert(&(*root)->r, data);
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
	printf("%c\n", root->data);

	draw__(root->l, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static int save__(FILE *fp, struct node_st *root)
{
	fprintf(fp, "(");

	if (root == NULL) {
		fprintf(fp, ")");
		return 0;
	}

	fprintf(fp, "%c", root->data);

	save__(fp, root->l);
	save__(fp, root->r);

	fprintf(fp, ")");

	return 0;
}

int save(const char *path, struct node_st *tree)
{
	FILE *fp;

	fp = fopen(path, "w");
	/* if error */

	save__(fp, tree);

	fclose(fp);

	return 0;
}

int main(void)
{
	struct node_st *tree = NULL;
	char arr[] = "362548971";
	//char arr[] = "213";
	int i;

	for (i = 0; i < sizeof(arr) - 1; i++) {
		insert(&tree, arr[i]);
	}

	draw(tree);
	save("tmp", tree);

	return 0;
}
