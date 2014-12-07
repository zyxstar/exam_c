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

#if 0
      __list_for_each(cur, &list) {
	    datap = list_entry(cur, struct score, node);
	    if (datap->id == 9) {
		  __list_del_entry(&datap->node);
		  free(datap);
	    }
      }
      printf("\n");
      __list_for_each(cur, &list) {
	    datap = list_entry(cur, struct score, node);
	    print_s(datap);
      }
#endif

      __list_for_each(cur, &list) {
	    datap = list_entry(cur, struct score, node);
	    if (datap->id == 5) {
		  break;
	    }
      }
      printf("\n");
      if (cur == &list) {
	    printf("Can not find.\n");
      } else {
	    print_s(datap);
      }

      return 0;
}
