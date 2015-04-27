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

static int save_construct(struct node_st *root, FILE *fp)
{
	if (root == NULL) {
		fprintf(fp, "0");
		return 0;
	}

	fprintf(fp, "1");

	save_construct(root->l, fp);
	save_construct(root->r, fp);

	return 0;
}

static int save_data(struct node_st *root, FILE *fp)
{
	if (root == NULL) {
		return 0;
	}

	fwrite(&root->data, sizeof(root->data), 1, fp);

	save_data(root->l, fp);
	save_data(root->r, fp);

	return 0;
}

int save(struct node_st *tree, const char *construct, const char *data)
{
	FILE *fpc, *fpd;

	fpc = fopen(construct, "w");
	/* if error */

	fpd = fopen(data, "w");

	save_construct(tree, fpc);
	save_data(tree, fpd);

	fclose(fpd);
	fclose(fpc);

	return 0;
}

int main(void)
{
	struct node_st *tree = NULL;
	int arr[] = {3,4,5,1,6,2,8,9,7};
	int i;
	struct stu tmp, *p;

	for (i = 0; i < sizeof(arr)/ sizeof(*arr); i++) {
		tmp.id = arr[i];
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		insert(&tree, &tmp);
	}

	draw(tree);
	save(tree, "construct", "data");

	return 0;
}
