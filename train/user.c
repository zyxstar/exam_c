#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

static void _destroy_user(void *data){
    USER *u = (USER*)data;
    DEBUG_WRITE(("_destroy_user: [name]%s, [passwd]%s\n",
        u->name, u->passwd));
    free(u->name);
    free(u->passwd);
}

LIST* init_users(){
    LIST *users = malloc(sizeof(LIST));
    list_new(users, sizeof(USER), _destroy_user);//need free
    return users;
}

void destroy_users(LIST *users){
    list_free(users);
    free(users);
}

static BOOL _cmp_user_name(void *exist, void *data){
    USER *e = (USER*)exist;
    USER *d = (USER*)data;
    return strcmp(e->name, d->name) == 0;
}

BOOL register_user(LIST *users, char *name, char *passwd){
    USER nu;
    nu.name = strdup(name);
    nu.passwd = strdup(passwd);
    return list_add_unique_elem(users, &nu, _cmp_user_name) != NULL;
}

static BOOL _cmp_user(void *exist, void *data){
    USER *e = (USER*)exist;
    USER *d = (USER*)data;
    return strcmp(e->name, d->name) == 0 && strcmp(e->passwd, d->passwd) == 0;
}

USER* validate_user(LIST *users, char *name, char *passwd){
    USER nu;
    nu.name = strdup(name);
    nu.passwd = strdup(passwd);
    int idx = list_find_idx(users, 0, &nu, _cmp_user);
    if(idx == -1) return NULL;
    return (USER*)list_get_elem_by_idx(users, idx);
}

static void _print_user(void *data, int idx, void *extra){
    USER *u = (USER*)data;
    printf("[%2d] [name] %-10s [passwd] %-10s\n", idx, u->name, u->passwd);
}

void list_users(LIST *users){
    list_each_elem_do(users, NULL, _print_user);
}


