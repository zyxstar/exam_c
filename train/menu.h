#include "list.h"
#include "utils.h"


typedef struct MENU_TAG{
    int id;
    int par_id;  // 0 means it's root's submenu
    int op;
    char *text;
    void(*call_fn)(struct MENU_TAG *cur, void *env);
    LIST *sub_menus;
} MENU;

MENU* init_menu();

void insert_menu(MENU *root, int id, int par_id, int op, char *text, void(*call_fn)(MENU *cur, void *env));

void show_menu(MENU *root, void *env);

void destroy_menu(MENU* root);
