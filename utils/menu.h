#include <list.h>
#include <console.h>


typedef struct MENU_TAG{
    int id;
    int par_id;  // 0 means it's root's submenu
    char *text;
    void(*call_fn)(struct MENU_TAG *cur, void *env);
    LIST *sub_menus;
} MENU;

void init_menu(MENU* root);
void destroy_menu(MENU* root);

void insert_menu(MENU *root, int id, int par_id, char *text, void(*call_fn)(MENU *cur, void *env));

void show_menu(MENU *root, void *env);

