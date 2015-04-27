#include "llist.h"
#include "queue.h"

LLIST* Creatqueue(int size)
{
	return llist_creat(size);
}
int Inqueue(LLIST *list, const void *data)
{
	return llist_add(list,data,LLIST_ADD_BACKWARD);
}
static int return_true(const void *a,const void *b)
{
	return 0;
}
void *Outqueue(LLIST * list)
{
	return llist_fetch(list, (void *)0,return_true);
}

void Destory(LLIST *list)
{
	llist_destroy(list);
}


