#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME   "dict"
#define DESC_SIZE  1024

struct node_st {
	struct node_st *child[26];
	char desc[DESC_SIZE];
};

struct word_st {
	char spell[DESC_SIZE];
	char desc[DESC_SIZE];
};

static int get_word(FILE *fp, struct word_st *word)
{
	char buf[DESC_SIZE];
	char *retp;

	retp = fgets(buf, DESC_SIZE, fp);
	if (retp == NULL) {
		return -1;
	}

	retp = strtok(buf, " \n");
	if (retp == NULL) {
		return -1;
	}
	strcpy(word->spell, retp); /* maybe ... */
	retp = strtok(NULL, " \n");
	strcpy(word->desc, retp); /* maybe ... */

	return 0;
}

static struct node_st *new_node(void)
{
	struct node_st *new;
	int i;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->desc[0] = '\0';
	for (i = 0; i < 26; i++) {
		new->child[i] = NULL;
	}

	return new;
}

static int insert__(struct node_st **root, struct word_st *word, const char *key)
{
	struct node_st *cur = *root;

	if (cur == NULL) {
		cur = new_node();
		/* if error */
		*root = cur;
	}

	if (*key == '\0') {
		strcpy(cur->desc, word->desc);
		return 0;
	}

	return insert__(&cur->child[*key - 'a'], word, key + 1);
}

int insert(struct node_st **root, struct word_st *word)
{
	return insert__(root, word, word->spell);
}

static int init(struct node_st **root)
{
	FILE *fp;
	struct word_st word;
	int ret;

	fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		perror(FILENAME);
		return -1;
	}

	while (1) {
		ret = get_word(fp, &word);
		if (ret == -1) {
			break;
		}

		insert(root, &word);
	}

	fclose(fp);
	return 0;
}

char *find(struct node_st *root, const char *key)
{
	if (root == NULL) {
		return NULL;
	}
	if (*key == '\0') {
		if (root->desc[0] == '\0') {
			return NULL;
		} else {
			return root->desc;
		}
	}
	return find(root->child[*key - 'a'], key + 1);
}

int main(void)
{
	struct node_st *tree = NULL;
	char *str;

	init(&tree);

	str = find(tree, "your");
	if (str == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%s\n", str);
	}

	//destroy(tree);

	return 0;
}
