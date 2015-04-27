#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_NR    128
#define NAMESIZE   32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
};

static struct score list[LIST_NR];

static int hash(int id)
{
	return id % LIST_NR;
}

int insert(const struct score *data)
{
	int ind;
	ind = hash(data->id);
	list[ind] = *data;

	return 0;
}

struct score *search(int id)
{
	int ind;
        ind = hash(id);

	return list + ind;
}

int main(void)
{
	struct score tmp, *data;
	int i;

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		insert(&tmp);
	}

	data = search(5);
	printf("%d %s %d\n", data->id, data->name, data->ch);

	return 0;
}
