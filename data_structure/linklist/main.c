#include <stdio.h>

#include "llist.h"

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

      struct score tmp, *datap;
      int i, id;
      LLIST *list;
      int ret;

      list = llist_creat(sizeof(struct score));

      for (i = 0; i < 7; i++) {
	    tmp.id = i;
	    tmp.math = 100 - i;
	    snprintf(tmp.name, NAMESIZE, "stu%d", i);

	    llist_insert(list, &tmp, LLIST_BACKWARD);
      }

      llist_travel(list, print_s);

      id = 4;
      ret = llist_fetch(list, &tmp, &id, id_cmp);
      printf("\n");
      if (ret == -1) {
	    printf("Can not find.\n");
      } else {
	    print_s(&tmp);
      }
      printf("\n");
      llist_travel(list, print_s);

#if 0
      id = 8;
      llist_delet(list, &id, id_cmp);
      printf("\n");
      llist_travel(list, print_s);
      id = 2;
      datap = llist_find(list, &id, id_cmp);
      if (datap == NULL) {
	    printf("Can not find.\n");
      } else {
	    print_s(datap);
      }
#endif
      llist_save(list, "stu.data");

      llist_destroy(list);

      LLIST *list2 = llist_load("stu.data");
      llist_travel(list2, print_s);
      llist_destroy(list2);
      

      return 0;
}
