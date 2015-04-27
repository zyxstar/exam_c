#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_st {
	char data;
	struct node_st *left, *right;
};

int insert(struct node_st **root, int data)
{
	struct node_st *newnode;

	if (*root == NULL) {
		newnode = malloc(sizeof(*newnode));
		if (newnode == NULL) {
			return -1;
		}
		newnode->data = data;
		newnode->left = newnode->right = NULL;
		*root = newnode;
		return 0;
	}

	if (data <= (*root)->data) {
		return insert(&(*root)->left, data);
	}
	return insert(&(*root)->right, data);
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
	printf("%c\n", root->data);
	draw__(root->left, level + 1);
}

void draw(struct node_st *root)
{
	draw__(root, 0);
}

static int save__(struct node_st *root, FILE *fp)
{
	if (root == NULL) {
		fputc(')', fp);
		return 0;
	}

	fputc(root->data, fp);
	save__(root->left, fp);
	save__(root->right, fp);

	fputc(')', fp);
}

int save(struct node_st *root, const char *path)
{
	FILE *fp;

	fp = fopen(path, "w");
	/* if error */

	save__(root, fp);

	fclose(fp);
	return 0;
}

int main(void)
{
	char id[] = "421367";
	int i;
	struct node_st *tree = NULL;

	for (i = 0; i < sizeof(id) / sizeof(*id) - 1; i++) {
		insert(&tree, id[i]);
	}

	draw(tree);
	save(tree, "tmp");
	return 0;
}
