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

static int save_st(struct node_st *root, FILE *fp)
{
	if (root == NULL) {
		fputc('0', fp);
		return 0;
	}

	fputc('1', fp);
	save_st(root->left, fp);
	save_st(root->right, fp);
}

static int save_d(struct node_st *root, FILE *fp)
{
	if (root == NULL) {
		return 0;
	}

	fwrite(&root->data, sizeof(root->data), 1, fp);
	save_d(root->left, fp);
	save_d(root->right, fp);
}

int save(struct node_st *root, const char *path_struct, const char *path_data)
{
	FILE *fp_st, *fp_d;

	fp_st = fopen(path_struct, "w");
	/* if error */

	fp_d = fopen(path_data, "w");
	/* if error */

	save_st(root, fp_st);
	save_d(root, fp_d);

	fclose(fp_d);
	fclose(fp_st);

	return 0;
}

int main(void)
{
	struct node_st *tree = NULL;
	int id[] = {5,3,7,1,2,4,6,8,9};
	int i;
	struct score tmp, *data;

	for (i = 0; i < sizeof(id) / sizeof(*id); i++) {
		tmp.id = id[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", id[i]);

		insert(&tree, &tmp);
	}

	draw(tree);
	save(tree, "tmp_struct", "tmp_data");

	return 0;
}
