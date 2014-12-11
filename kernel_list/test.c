#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define NAMESIZE 32

struct score {
      int id;
      char name[NAMESIZE];
      int math;
      struct list_head node;
};

void print_s(void *data)
{
      struct score *d = data;
      printf("%d %s %d\n", d->id, d->name, d->math);
}

int main(void)
{
      struct score *datap;
      int i;
      struct list_head *cur;

      LIST_HEAD(list);


      list_add(&datap->node, &list);

      return 0;
}
