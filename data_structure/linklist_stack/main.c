#include <stdio.h>

#include "stack.h"

#define NAMESIZE 32

struct score {
      int id;
      char name[NAMESIZE];
      int math;
};

void print_s(void *data)
{
      struct score *d = data;
      printf("%d %s %d\n", d->id, d->name, d->math);
}

int id_cmp(const void *key, const void *record)
{
      const int *id = key;
      const struct score *r = record;

      return *id - r->id;
}

int main(void)
{
      struct score tmp;
      STACK *list;
      int ret;
      int i;

      list = stack_creat(sizeof(struct score));

      for (i = 0; i < 7; i++) {
	    tmp.id = i;
	    tmp.math = 100 - i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i);

	    stack_push(list, &tmp);
      }

      for (i = 0; i < 9; i++) {
	    ret = stack_pop(list, &tmp);
	    if (ret == -1) {
		  printf("stack empty.\n");
		  break;
	    }
	    print_s(&tmp);
      }

      stack_destroy(list);

      return 0;
}
