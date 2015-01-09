#include <stdlib.h>
#include "kernel_list.h"
#include "kernel_list_helper.h"
#include "event.h"

typedef struct{
    EVENT_HANDLER *handler;
    void *receiver;
    struct list_head node;
} _HANDLER_NODE;



EVENT *event_new(void *sender){
    EVENT *e = malloc(sizeof(*e));
    INIT_LIST_HEAD(&e->handlers);
    e->sender = sender;
    return e;
}




// declare
void _event_each_handler(EVENT *, void *env, void(*each_do)(_HANDLER_NODE *, int idx, void *env));
// implement
_implement_list_each(_event_each_handler, EVENT, handlers, _HANDLER_NODE, node);

static void _event_handler_node_free(_HANDLER_NODE *h_node, int idx, void *env){
    free(h_node);
}

void event_free(EVENT *e){
    _event_each_handler(e, NULL, _event_handler_node_free);
    free(e);
}






void event_add(EVENT *e, void *receiver, EVENT_HANDLER *h){
    _HANDLER_NODE *h_node = malloc(sizeof(*h_node));
    h_node->receiver = receiver;
    h_node->handler = h;
    list_add_tail(&h_node->node, &e->handlers);
}






// declare
_HANDLER_NODE *_event_find_handler(EVENT *, const void *key, int(*cmp)(const void *key, const _HANDLER_NODE *));
// implement
_implement_list_find(_event_find_handler, EVENT, handlers, _HANDLER_NODE, node);

static _handler_cmp(const void *key, const _HANDLER_NODE *h_node){
    void *r = ((void **)key)[0];
    EVENT_HANDLER *h = ((void **)key)[1];
    return r == h_node->receiver && h == h_node->handler;
}


void event_remove(EVENT *e, void *receiver, EVENT_HANDLER *h){
    void *key[] = {receiver, h};
    _HANDLER_NODE *h_node = _event_find_handler(e, key, _handler_cmp);
    if(h_node == NULL) return;
    __list_del_entry(&h_node->node);
    free(h_node);
}








static void _event_handler_node_trigger(_HANDLER_NODE *h_node, int idx, void *env){
    void **envs = env;
    h_node->handler(envs[0], h_node->receiver, envs[1]);
}

void event_trigger(EVENT *e, void *arg){
    void *env[] = {e->sender, arg};
    _event_each_handler(e, env, _event_handler_node_trigger);
}
