#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "menu.h"


void init_menu(MENU *root){
    root->id = 0;
    root->par_id = -1;
    root->text = strdup("root");
    root->sub_menus = NULL;
}

static MENU* _get_menu_by_id(MENU *menu, int id){
    DEBUG_WRITE(("_get_menu_by_id: [id]%d\n", id));
    if(menu->id == id) return menu;
    if(menu->sub_menus == NULL) return NULL;
    MENU *ret = NULL;
    int i;
    for(i = 0; i < menu->sub_menus->used_len; i++){
        MENU *m = (MENU*)list_get_elem_by_idx(menu->sub_menus, i);
        ret = _get_menu_by_id(m, id);
        if(ret != NULL) return ret;
    }
    return NULL;
}

static void _destroy_menu(void *data){
    MENU* menu = (MENU*)data;
    int id = menu->id;
    DEBUG_WRITE(("_destroy_menu begin: [id]%d, [text]%s, [sub_menus]%p\n",
        id, menu->text, menu->sub_menus));
    free(menu->text);

    if(menu->sub_menus != NULL){
        list_free(menu->sub_menus);
        free(menu->sub_menus);
    }
    DEBUG_WRITE(("_destroy_menu end: [id]%d\n", id));
}

void destroy_menu(MENU* root){
    _destroy_menu(root);
}

//////////////////////////////////////////////



void insert_menu(MENU *root, int id, int par_id, int op, char *text,
                 void(*call_fn)(MENU *cur, void *env)){
    DEBUG_WRITE(("insert_menu begin: [id]%d, [pid]%d\n", id, par_id));
    MENU *target = _get_menu_by_id(root, par_id);
    assert(target != NULL);
    if(target->sub_menus == NULL){
        target->sub_menus = malloc(sizeof(LIST));
        list_new(target->sub_menus, sizeof(MENU), _destroy_menu);
    }
    MENU m = {id, par_id, op, strdup(text), call_fn};
    list_add_elem(target->sub_menus, &m);
    DEBUG_WRITE(("insert_menu end: [id]%d, [pid]%d\n", id, par_id));
}



//////////////////////////////////////////////


static void _show_menu_item_fn(void* data, int idx, void* extra){
    MENU *m = (MENU*)data;
    printf_info("   "VT_LIGHT VT_BLACK"[%2d]"VT_RESET VT_YELLOW" %s\n", m->op, m->text);
}

static void _show_sub_menu(MENU *m){
    if(m->sub_menus == NULL){
        printf_info("   module still in development\n");
        return;
    }
    list_each_elem_do(m->sub_menus, NULL, _show_menu_item_fn);
}

static void _show_cur_menu(MENU *cur_menu){
    printf_info(VT_LIGHT VT_BLACK"-> [%s]\n"VT_RESET, cur_menu->text);
    _show_sub_menu(cur_menu);
    if(cur_menu->id != 0)
        printf_info("   "VT_LIGHT VT_BLACK"[ 0]"VT_RESET VT_YELLOW" back\n");
    printf_info("   "VT_LIGHT VT_BLACK"[-1]"VT_RESET VT_YELLOW" quit\n");
}




static BOOL _cmp_menu_fn(void *exist, void *data){
    return ((MENU*)exist)->op == *((int*)data);
}

static BOOL _change_menu(MENU **cur_menu, int op){// must MENU**
    // printf("menu[%d]", op);
    if((*cur_menu)->sub_menus == NULL) return FALSE;
    int idx = list_find_idx((*cur_menu)->sub_menus, 0, &op, _cmp_menu_fn);
    if(idx == -1) return FALSE;
    *cur_menu = (MENU*)list_get_elem_by_idx((*cur_menu)->sub_menus, idx);
    // printf("[%s]\n", (*cur_menu)->text);
}

static void _back_menu(MENU *root, MENU **cur_menu){// must MENU**
    int par_id = (*cur_menu)->par_id;
    if(par_id == -1) return;
    *cur_menu = (MENU*)_get_menu_by_id(root, par_id);
}

void show_menu(MENU *root, void *env){
    MENU *cur_menu = root;
    int op = -2;
    // char buf[256];
    while(1){
        _show_cur_menu(cur_menu);

        // fgets(buf, sizeof(buf), stdin);
        // sscanf(buf, "%d", &op);
        op = -2;
        scanf("%d", &op);
        getchar();

        if(op == -1) break;
        if(op == 0) {
            _back_menu(root, &cur_menu);
            continue;
        }

        if(_change_menu(&cur_menu, op)){
            //printf("_change_menu cur_menu[%s]\n", cur_menu->text);
            if(cur_menu->call_fn == NULL)
                continue;
            else{
                printf(VT_LIGHT VT_BLACK"-> [%s]\n"VT_RESET, cur_menu->text);
                cur_menu->call_fn(cur_menu, env);
                _back_menu(root, &cur_menu);
            }
        }
        else
            printf_error("-> error code, choice again:\n");

    }
}




