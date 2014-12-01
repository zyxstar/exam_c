#include "utils.h"
#include "list.h"
#include <stdio.h>

typedef struct{
    char *name; //char pointer, need free
    char *passwd;
} USER;

LIST* init_users();
//void init_users(LIST*); //maybe better than above
void destroy_users(LIST *users);

BOOL register_user(LIST *users, char *name, char *passwd);
USER* validate_user(LIST *users, char *name, char *passwd);

void list_users(LIST *users);

void save_users(LIST *users, FILE* fp);
LIST* load_users(FILE* fp);
