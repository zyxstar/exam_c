#ifndef LIST_H_INCLUEDE
#define LIST_H_INCLUEDE

#include "utils.h"
#include <stdio.h>

typedef struct{
    void *header;
    int elem_size;
    int used_len;
    int alloc_len;
    void(*free_elem_fn)(void*);
} LIST;

void list_new(LIST *list, int elem_size, void(*free_elem_fn)(void*));
void list_free(LIST *list);

void* list_add_elem(LIST *list, void *data);
void* list_add_unique_elem(LIST *list, void *data, BOOL(*cmp_fn)(void* exist, void* data));
void* list_get_elem_by_idx(LIST *list, int idx);
int list_find_idx(LIST *list, int start_idx, void *extra, BOOL(*cmp_fn)(void* exist, void* extra));

void list_each_elem_do(LIST *list, void *extra, void(*do_fn)(void* data, int idx, void* extra));

void list_save(LIST *list, FILE *fp, void(*save_elem_fn)(void *elem, FILE *fp));
void list_load(LIST *list, FILE *fp, void(*load_elem_fn)(void *elem, FILE *fp), void(*free_elem_fn)(void*));


typedef LIST STACK;

void stack_new(STACK *stack, int elem_size, void(*free_elem_fn)(void*));
void stack_free(STACK *stack);

void* stack_push(STACK *stack, void *data);
void stack_pop(STACK *stack, void *data);



#endif /*LIST_H_INCLUEDE*/
