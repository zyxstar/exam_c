#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"
#include "list.h"

// menu logic
typedef struct{
    int id;
    int par_id;
    int op;
    char *text;
    void(*call_fn)();
    LIST *sub_menus;
} MENU;

MENU *cur_menu;

static void _show_menu_item_fn(void* data, int idx, void* extra){
    MENU *m = (MENU*)data;
    printf("[%d]%s\n", m->op, m->text);
}

static BOOL _show_sub_menu(MENU *m){
    if(m->sub_menus == NULL){
        printf("empty yet!\n");
        return FALSE;
    }
    list_each_elem_do(m->sub_menus, NULL, _show_menu_item_fn);
    return TRUE;
}

static BOOL _show_cur_menu(){
    return _show_sub_menu(cur_menu);
}

static BOOL _cmp_menu_fn(void *exist, void *data){
    return ((MENU*)exist)->op == *((int*)data);
}

static BOOL _change_menu(int op){
    printf("menu[%d]", op);
    int idx = list_find_idx(cur_menu->sub_menus, 0, &op, _cmp_menu_fn);
    if(idx == -1) return FALSE;
    cur_menu = (MENU*)list_get_elem_by_idx(cur_menu->sub_menus, idx);
    printf("[%s]\n", cur_menu->text);

}

static MENU* _get_menu_by_id(MENU *menu, int id){
    if(menu->id == id) return menu;
    int i;
    for(i = 0; i < menu->sub_menus->used_len; i++){
        MENU *m = (MENU*)list_get_elem_by_idx(menu->sub_menus, i);
        return _get_menu_by_id(m, id);
    }
}

static void _insert_menu(MENU *root, int id, int par_id, int op, char *text, void(*call_fn)()){
    MENU *target = _get_menu_by_id(root, par_id);
    if(target->sub_menus == NULL){
        target->sub_menus = malloc(sizeof(LIST));
        list_new(target->sub_menus, sizeof(MENU), NULL);// free text, free sub
    }
    MENU m = {id, par_id, op, strdup(text), call_fn};
    list_add_elem(target->sub_menus, &m);
}


static void _build_menu(MENU **menus, int size){
    int i, j;
    for(i = 0; i < size-1; i++){
        for(j = i + 1; j < size; j++){
            if(menus[j]->par_id == menus[i]->id){
                if(menus[i]->sub_menus == NULL){
                    menus[i]->sub_menus = malloc(sizeof(LIST));
                    list_new(menus[i]->sub_menus, sizeof(MENU), NULL);
                }
                list_add_elem(menus[i]->sub_menus, menus[j]);
            }
        }
    }
    printf("_build_menu %p\n", menus[1]->sub_menus);
    MENU *m1 = (MENU*)list_get_elem_by_idx(menus[0]->sub_menus, 0);
    printf("_build_menu %p\n", m1->sub_menus);

}


MENU* prepare_menus();

void show_menu(){
    MENU *root = prepare_menus();
    cur_menu = root;
    int op;
    while(1){
        printf("cur_menu[%s]\n", cur_menu->text);
        _show_sub_menu(cur_menu);

LOOP:
        scanf("%d", &op);
        if(op == 0) break;
        if(_change_menu(op)){
            printf("cur_menu[%s]\n", cur_menu->text);
            if(cur_menu->call_fn == NULL){
                if(_show_cur_menu())
                    goto LOOP;
            }
            else
                cur_menu->call_fn();
        }
        cur_menu = root;
    }
}










// ui logic

LIST user_list = {0};

void register_user_ui(){
    char name[10], passwd[10];
    printf("username: ");
    scanf("%s", name);
    printf("password: ");
    scanf("%s", passwd);
    if(register_user(&user_list,name,passwd))
        printf("resigter successful\n");
    else
        printf("resigter failed: user exist\n");
}

void validate_user_ui(){
    char name[10], passwd[10];
    printf("username: ");
    scanf("%s", name);
    printf("password: ");
    scanf("%s", passwd);
    if(validate_user(&user_list,name,passwd))
        printf("login successful\n");
    else
        printf("login failed\n");
}

void list_users_ui(){
    list_users(&user_list);
}







// menu config
MENU* prepare_menus(){
    MENU *root = malloc(sizeof(MENU));
    root->id = 0;
    root->text = strdup("root");

    _insert_menu(root, 1, 0, 1, "manage users", NULL);
    _insert_menu(root, 2, 0, 2, "manage trains", NULL);
    _insert_menu(root, 3, 0, 3, "manage tickets", NULL);
    _insert_menu(root, 4, 1, 1, "register", register_user_ui);
    _insert_menu(root, 5, 1, 2, "login", validate_user_ui);
    _insert_menu(root, 6, 1, 3, "list users", list_users_ui);

    return root;
}



// app
int main(){

    show_menu();

    destroy_users(&user_list);
    return 0;
}



// gcc -DDEBUG utils.c list.c train.c app.c -o app.out && ./app.out
// gcc utils.c list.c train.c app.c -o app.out && ./app.out
