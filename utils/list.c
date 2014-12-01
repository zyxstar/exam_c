#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

#define INIT_ALLOC_LEN (1)

static void _list_grow(LIST *list){
    DEBUG_WRITE(("_list_grow begin: [alloc_len]%d, [header]%p\n", list->alloc_len, list->header));
    list->alloc_len *= 2;
    list->header = realloc(list->header, list->alloc_len * list->elem_size);
    assert(list->header != NULL);
    DEBUG_WRITE(("_list_grow end: [alloc_len]%d, [header]%p\n", list->alloc_len, list->header));
}

void list_new(LIST *list, int elem_size, void(*free_elem_fn)(void*)){
    DEBUG_WRITE(("list_new begin: [elem_size]%d\n", elem_size));
    assert(elem_size > 0);
    list->elem_size = elem_size;
    list->used_len = 0;
    list->alloc_len = INIT_ALLOC_LEN;
    list->free_elem_fn = free_elem_fn;
    list->header = malloc(INIT_ALLOC_LEN * elem_size);
    assert(list->header != NULL);
    DEBUG_WRITE(("list_new end\n"));
}

void* list_add_elem(LIST *list, void *data){
    DEBUG_WRITE(("list_add_elem begin: [used_len]%d\n", list->used_len));
    assert(list->alloc_len >= list->used_len);
    if(list->alloc_len == list->used_len)
        _list_grow(list);

    void *target = (char*)list->header + list->used_len * list->elem_size;
    memcpy(target, data, list->elem_size);
    list->used_len++;
    DEBUG_WRITE(("list_add_elem end: [used_len]%d\n", list->used_len));
    return target;
}


void* list_add_unique_elem(LIST *list, void *data, BOOL(*cmp_fn)(void*, void*)){
    int i;
    void *exist_data;
    for(i = 0; i < list->used_len; i++){
        exist_data = list_get_elem_by_idx(list, i);
        if(cmp_fn(exist_data, data)) return NULL;
    }
    return list_add_elem(list, data);
}

void* list_get_elem_by_idx(LIST *list, int idx){
    DEBUG_WRITE(("list_get_elem_by_idx begin: [idx]%d\n", idx));
    void *ret = (char*)list->header + list->elem_size * idx;
    DEBUG_WRITE(("list_get_elem_by_idx end: [idx]%d\n", idx));
    return ret;
}

int list_find_idx(LIST *list, int start_idx, void *extra, BOOL(*cmp_fn)(void*, void*)){
    int i;
    for(i = start_idx; i < list->used_len; i++)
        if(cmp_fn(list_get_elem_by_idx(list, i), extra))
            return i;
    return -1;
}

void list_each_elem_do(LIST *list, void *extra, void(*do_fn)(void*, int, void*)){
    int i;
    for(i = 0; i < list->used_len; i++)
        do_fn(list_get_elem_by_idx(list, i), i, extra);
}

void list_free(LIST *list){
    DEBUG_WRITE(("list_free begin\n"));
    int i;
    if(list->free_elem_fn != NULL){
        for(i = 0; i < list->used_len; i++){
            DEBUG_WRITE(("list_free_sub begin: [idx]%d\n", i));
            list->free_elem_fn((char*)list->header + i * list->elem_size);
            DEBUG_WRITE(("list_free_sub end: [idx]%d\n", i));
        }
    }
    free(list->header);
    DEBUG_WRITE(("list_free end\n"));
}

void list_save(LIST *list, FILE *fp, void(*save_elem_fn)(void*, FILE*)){
    assert(fp != NULL);
    DEBUG_WRITE(("list_save begin\n"));
    fwrite(list, sizeof(LIST), 1, fp); //LIST
    int i;
    void *elem;
    for(i = 0; i<list->used_len; i++){
        elem = list_get_elem_by_idx(list, i);
        DEBUG_WRITE(("list_save_elem begin: [idx]%d\n", i));
        fwrite(elem, list->elem_size, 1, fp);//elem
        DEBUG_WRITE(("list_save_elem end: [idx]%d\n", i));

        if(save_elem_fn != NULL){
            //if elem is a pointer
            DEBUG_WRITE(("list_save_elem_ref begin: [idx]%d\n", i));
            save_elem_fn(elem, fp);
            DEBUG_WRITE(("list_save_elem_ref begin: [idx]%d\n", i));
        }
    }
    DEBUG_WRITE(("list_save end\n"));
}

void list_load(LIST *list, FILE *fp, void(*load_elem_fn)(void*, FILE*), void(*free_elem_fn)(void*)){
    assert(fp != NULL);
    DEBUG_WRITE(("list_load begin\n"));
    fread(list, sizeof(LIST), 1, fp); //LIST
    DEBUG_WRITE(("list_load [alloc_len]:%d, [used_len]:%d\n", list->alloc_len, list->used_len));
    list->header = malloc(list->alloc_len * list->elem_size);
    list->free_elem_fn = free_elem_fn;

    int i;
    void *elem;
    for(i = 0; i<list->used_len; i++){
        elem = list_get_elem_by_idx(list, i);
        DEBUG_WRITE(("list_load_elem begin: [idx]%d\n", i));
        fread(elem, list->elem_size, 1, fp);//elem
        DEBUG_WRITE(("list_load_elem end: [idx]%d\n", i));

        if(load_elem_fn != NULL){
            //if elem is a pointer
            DEBUG_WRITE(("list_load_elem_ref begin: [idx]%d\n", i));
            load_elem_fn(elem, fp);
            DEBUG_WRITE(("list_load_elem_ref begin: [idx]%d\n", i));
        }
    }
    DEBUG_WRITE(("list_load end\n"));
}


////////////////////////////////
void stack_new(STACK *stack, int elem_size, void(*free_elem_fn)(void*)){
    list_new((LIST*)stack, elem_size, free_elem_fn);
}

void stack_free(STACK *stack){
    list_free((LIST*)stack);
}

void* stack_push(STACK *stack, void *data){
    return list_add_elem((LIST*)stack, data);
}

void stack_pop(STACK *stack, void *data){
    DEBUG_WRITE(("stack_pop begin: [used_len]%d\n", stack->used_len));
    assert(stack->used_len > 0);

    stack->used_len--;
    void *source = (char*)stack->header + stack->used_len * stack->elem_size;
    memcpy(data, source, stack->elem_size);
    DEBUG_WRITE(("stack_pop end: [used_len]%d\n", stack->used_len));
}

// void string_free_elem_fn(void* elemAddr) {
//     char** p = (char**)elemAddr;
//     free(*p);
// }

// void test_stack(){
//     const char friends[][5] = {"Al", "Bob", "Carl"};
//     STACK string_stack;
//     int i;
//     stack_new(&string_stack, sizeof(char*));
//     for(i = 0; i < 3; i++) {
//         char *copy = strdup(friends[i]);
//         stack_push(&string_stack, &copy);
//     }
//     char* name;
//     while(string_stack.used_len > 0) {
//         stack_pop(&string_stack, &name);
//         printf("%s\n", name);
//         free(name);
//     }
//     stack_free(&string_stack, string_free_elem_fn);
// }
