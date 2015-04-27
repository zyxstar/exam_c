#ifndef  _BSL_QUEUE_
#define  _BSL_QUEUE_

#include<stdio.h>
#include<stdlib.h>
#include "llist.h"

int Inqueue(LLIST *, const void *data);

void *Outqueue(LLIST *);

void Destory(LLIST *);

LLIST* Creatqueue(int size);

#endif
