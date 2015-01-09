#ifndef KERNEL_LIST_HELPER_H_INCLUEDE
#define KERNEL_LIST_HELPER_H_INCLUEDE

#include <stdio.h>
#include "kernel_list.h"

#define __list_for_each_wrap(container_type, container_list_member, entry_type, entry_node_member, body)\
    struct list_head *cur;\
    entry_type *entry;\
    int idx = 0;\
    __list_for_each(cur, &ptr->container_list_member) {\
        entry = list_entry(cur, entry_type, entry_node_member);\
        body;\
        idx++;\
    }\


#define _implement_list_each(fun_name, container_type, container_list_member, entry_type, entry_node_member)\
    void fun_name(container_type *ptr, void *env, void(*each_do)(entry_type *entry, int idx, void *env)){\
        __list_for_each_wrap(container_type, container_list_member, entry_type, entry_node_member, \
            each_do(entry, idx, env);\
        )\
    }\


#define _implement_list_find(fun_name, container_type, container_list_member, entry_type, entry_node_member)\
    entry_type *fun_name(container_type *ptr, const void *key, int(*cmp)(const void *key, const entry_type *entry)){\
        __list_for_each_wrap(container_type, container_list_member, entry_type, entry_node_member, \
            if(cmp(key, entry) == 0)\
                return entry;\
        )\
        return NULL;\
    }\


#define _implement_list_save(fun_name, container_type, container_list_member, entry_type, entry_node_member)\
    void fun_name(container_type *ptr, FILE *fp, void(*entry_save)(entry_type *, FILE *)){\
        long offset_count, offset_stream;\
        fwrite(ptr, sizeof(container_type), 1, fp);\
        offset_count = ftell(fp);\
        int count = 0;\
        fseek(fp, sizeof(int), SEEK_CUR);\
        __list_for_each_wrap(container_type, container_list_member, entry_type, entry_node_member, \
            entry_save(entry, fp);\
            count = idx + 1;\
        )\
        offset_stream = ftell(fp);\
        fseek(fp, offset_count, SEEK_SET);\
        fwrite(&count, sizeof(count), 1, fp);\
        fseek(fp, offset_stream, SEEK_SET);\
    }\

#define _implement_list_load(fun_name, container_type, container_list_member)\
    container_type *fun_name(FILE *fp, void(*config_container)(container_type *), void(*entry_load)(container_type *, FILE *)){\
        container_type *ptr = malloc(sizeof(container_type));\
        fread(ptr, sizeof(container_type), 1, fp);\
        INIT_LIST_HEAD(&ptr->container_list_member);\
        int i, count;\
        fread(&count, sizeof(int), 1, fp);\
        config_container(ptr);\
        for(i = 0; i < count; i++)\
            entry_load(ptr, fp);\
        return ptr;\
    }\


#endif


