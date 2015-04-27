#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHILD_NR    26
#define WORDSIZE    32
#define DESCSIZE    1024
#define BUFSIZE     1024

struct node_st {
	struct node_st *child[CHILD_NR];
	char *str;
};

int get_word(FILE *fp, char word[WORDSIZE], char desc[DESCSIZE])
{
	char buf[BUFSIZE];
	char *p;

	p = fgets(buf, BUFSIZE, fp);
	if (p == NULL) {
		return -1;
	}
	if (buf[0] == '\n') {
		return -1;
	}
	sscanf(buf, "%s %s\n", word, desc);

	return 0;
}

static void *alloc_node(void)
{
	struct node_st *node;
	int i;

	node = malloc(sizeof(*node));
	/* if error */
	node->str = NULL;
	for (i = 0; i < 26; i++) {
		node->child[i] = NULL;
	}
	return node;
}

int insert(struct node_st **root, const char *word, const char *desc)
{
	if (*root == NULL) {
		*root = alloc_node();
		/* if error */
	}

	if (*word == '\0') {
		(*root)->str = strdup(desc);
		return 0;
	}
	return insert(&(*root)->child[*word - 'a'], word + 1, desc);
}

char *search(struct node_st *root, const char *word)
{
	if (root == NULL) {
		return NULL;
	}
	if (*word == '\0') {
		return root->str;
	}
	return search(root->child[*word - 'a'], word + 1);
}

int main(void)
{
	struct node_st *tree = NULL;
	char word[WORDSIZE];
	char desc[DESCSIZE];
	char *str;
	FILE *fp;
	int ret;

	fp = fopen("dict.txt", "r");
	/* if error */

	while (1) {
		ret = get_word(fp, word, desc);
		if (ret == -1) {
			break;
		}

		printf("debug, will insert: %s %s\n", word, desc);
		insert(&tree, word, desc);
		printf("debug, insert() return\n");
	}

	fclose(fp);

	str = search(tree, "aaaaa");
	if (str == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%s\n", str);
	}

	return 0;
}
