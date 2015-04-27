#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_st {
	char data;
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
	printf("%c\n", root->data);
	draw__(root->left, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static struct node_st *load__(FILE *fp)
{
	int data;
	struct node_st *root;

	data = fgetc(fp);
	if (data == ')') {
		return NULL;
	}

	root = malloc(sizeof(*root));
	/* if error */
	root->data = data;
	root->left = load__(fp);
	root->right = load__(fp);
	fgetc(fp);		/* get ')' */

	return root;
}

struct node_st *load(const char *path)
{
	FILE *fp;
	struct node_st *root;

	fp = fopen(path, "r");
	/* if error */

	root = load__(fp);

	fclose(fp);

	return root;
}

int main(void)
{
	struct node_st *tree = NULL;

	tree = load("tmp");

	draw(tree);
	return 0;
}
