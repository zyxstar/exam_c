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

      for (i = 0; i < 7; i++) {
        datap = malloc(sizeof(*datap));
        /* if error */

        datap->id = i;
        datap->math = 100 - i;
        snprintf(datap->name, NAMESIZE, "stu%d", i);

        list_add(&datap->node, &list);
      }

      __list_for_each(cur, &list) {
        datap = list_entry(cur, struct score, node);
        print_s(datap);
      }



      return 0;
}
