  LIST_HEAD(list);

struct list_head list =  { &(list), &(list) };

 for (cur = (&list)->next; cur != (&list); cur = cur->next){

  datap = (struct score *)( (char *)cur - ((size_t) &((struct score *)0)->node) );


print_s(datap);






