#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static struct node_st *load__(FILE *fp_st, FILE *fp_d)
{
	struct node_st *root;
	char flag;

	flag = fgetc(fp_st);
	if (flag == '0') {
		return NULL;
	}

	root = malloc(sizeof(*root));
	/* if error */
	fread(&root->data, sizeof(root->data), 1, fp_d);

	root->left = load__(fp_st, fp_d);
	root->right = load__(fp_st, fp_d);

	return root;
}

struct node_st *load(const char *path_st, const char *path_d)
{
	FILE *fp_st, *fp_d;
	struct node_st *root;

	fp_st = fopen(path_st, "r");
	/* if error */
	fp_d =fopen(path_d, "r");
	/* if error */

	root = load__(fp_st, fp_d);

	fclose(fp_d);
	fclose(fp_st);

	return root;
}

int main(void)
{
	struct node_st *tree = NULL;

	tree = load("tmp_struct", "tmp_data");
	draw(tree);

	return 0;
}
