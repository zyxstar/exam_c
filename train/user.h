#include "utils.h"
#include "list.h"

typedef struct{
    char *name; //char pointer, need free
    char *passwd;
} USER;

LIST* init_users();
void destroy_users(LIST *users);

BOOL register_user(LIST *users, char *name, char *passwd);
USER* validate_user(LIST *users, char *name, char *passwd);

void list_users(LIST *users);
