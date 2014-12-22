#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "user.h"

static void _destroy_user(void *data){
    USER *u = (USER*)data;
    DEBUG_WRITE(("_destroy_user: [name]%s, [passwd]%s\n",
        u->name, u->passwd));
    free(u->name);
    free(u->passwd);
}

void init_users(LIST *users){//caller will assign `users` memory
    list_new(users, sizeof(USER), _destroy_user);//need free
}

void destroy_users(LIST *users){
    list_free(users);
    //caller will [auto] free `users` memory
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

static void _save_user(void *elem, FILE *fp){
    USER *user = (USER*)elem;
    char name[10], passwd[10];
    strcpy(name, user->name);
    strcpy(passwd, user->passwd);
    fwrite(name, sizeof(char), 10, fp);
    fwrite(passwd, sizeof(char), 10, fp);
}

void save_users(LIST *users, FILE* fp){
    list_save(users, fp, _save_user);
}

static void _load_user(void *elem, FILE *fp){
    char name[10], passwd[10];
    fread(name, sizeof(char), 10, fp);
    fread(passwd, sizeof(char), 10, fp);
    USER *user = (USER*)elem;
    user->name = strdup(name);
    user->passwd = strdup(passwd);
}

void load_users(LIST *users, FILE* fp){
    list_load(users, fp, _load_user, _destroy_user);
}
