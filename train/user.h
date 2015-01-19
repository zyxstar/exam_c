#include <stdio.h>
#include <list.h>
#include <console.h>

typedef struct{
    char *name; //char pointer, need free
    char *passwd;
} USER;

//return pointer of LIST see `git branch BR_01`
//this version is better than that
void init_users(LIST *users);

void destroy_users(LIST *users);

BOOL register_user(LIST *users, char *name, char *passwd);
USER* validate_user(LIST *users, char *name, char *passwd);

void list_users(LIST *users);

void save_users(LIST *users, FILE *fp);
void load_users(LIST *users, FILE *fp);
