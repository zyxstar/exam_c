#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NAMESIZE 32

struct node_st {
	char data;
	struct node_st *l, *r;
};

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

static struct node_st *load__(FILE *fp)
{
	struct node_st *node;
	char c;

	/* get ( */
	fgetc(fp);

	/* get data */
	c = fgetc(fp);
	if (c == ')') {
		return NULL;
	}

	node = malloc(sizeof(*node));
	node->data = c;

	node->l = load__(fp);
	node->r = load__(fp);

	/* get ) */
	fgetc(fp);

	return node;
}

struct node_st *load(const char *path)
{
	FILE *fp;
	struct node_st *tree;

	fp = fopen(path, "r");
	/* if error */

	tree = load__(fp);

	fclose(fp);

	return tree;
}

int main(void)
{
	struct node_st *tree;

	tree = load("tmp");
	draw(tree);

	return 0;
}
