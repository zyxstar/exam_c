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

static void print_stu(struct stu *data)
{
	printf("%d %s\n", data->id, data->name);
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

static struct node_st *load__(FILE *fpc, FILE *fpd)
{
	struct node_st *node;
	char c;

	/* get data */
	c = fgetc(fpc);
	if (c == '0') {
		return NULL;
	}

	node = malloc(sizeof(*node));
	//node->data = c;
	fread(&node->data, sizeof(node->data), 1, fpd);

	node->l = load__(fpc, fpd);
	node->r = load__(fpc, fpd);

	return node;
}

struct node_st *load(const char *construct, const char *data)
{
	FILE *fpc, *fpd;
	struct node_st *tree;

	fpc = fopen(construct, "r");
	/* if error */

	fpd = fopen(data, "r");
	/* if error */

	tree = load__(fpc, fpd);

	fclose(fpd);
	fclose(fpc);

	return tree;
}

int main(void)
{
	struct node_st *tree = NULL;

	tree = load("construct", "data");
	draw(tree);

	return 0;
}
