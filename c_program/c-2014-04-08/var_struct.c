#include <stdio.h>

struct score {
	int id;
	int math;
	char name[1];
};

struct xxx {
	int other;
	char data[0];
};

int main(void)
{
	struct score *p;
	const char *name = "shrek";

	p = malloc(sizeof(*p) + strlen(name));
	/* if error */

	p->id = 0;
	p->math = 59;
	strcpy(p->name, name);

	return 0;
}
