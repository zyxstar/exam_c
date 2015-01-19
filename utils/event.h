#ifndef EVENT_H_INCLUEDE
#define EVENT_H_INCLUEDE

#include <stdio.h>
#include <kernel_list.h>


typedef struct{
    void *sender;
    struct list_head handlers;
} EVENT;

typedef void EVENT_HANDLER(void *sender, void *receiver, void *arg);


EVENT *event_new(void *sender);
void event_free(EVENT *);

void event_add(EVENT *, void *receiver, EVENT_HANDLER *);
void event_remove(EVENT *, void *receiver, EVENT_HANDLER *);
void event_trigger(EVENT *, void *arg);

#endif
