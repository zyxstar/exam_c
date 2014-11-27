#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "menu.h"


MENU* init_menu(){
    MENU *root = malloc(sizeof(MENU));
    root->id = 0;
    root->par_id = -1;
    root->text = strdup("root");
    return root;
}

static MENU* _get_menu_by_id(MENU *menu, int id){
    // printf("mnue %d\n", menu->id);
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



//////////////////////////////////////////////

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

void insert_menu(MENU *root, int id, int par_id, int op, char *text,
                 void(*call_fn)(MENU *cur, void *env)){
    // printf("id %d pid %d\n", id, par_id);
    MENU *target = _get_menu_by_id(root, par_id);
    assert(target != NULL);
    // printf("pid===%d\n", target->id);

    if(target->sub_menus == NULL){
        target->sub_menus = malloc(sizeof(LIST));
        list_new(target->sub_menus, sizeof(MENU), _destroy_menu);
    }
    MENU m = {id, par_id, op, strdup(text), call_fn};
    list_add_elem(target->sub_menus, &m);
}






//////////////////////////////////////////////



static void _show_menu_item_fn(void* data, int idx, void* extra){
    MENU *m = (MENU*)data;
    printf_info("   "DARY_GRAY"[%2d]"BROWN" %s\n", m->op, m->text);
}

static void _show_sub_menu(MENU *m){
    if(m->sub_menus == NULL){
        printf_info("   empty yet!\n");
        return;
    }
    list_each_elem_do(m->sub_menus, NULL, _show_menu_item_fn);
}

static void _show_cur_menu(MENU *cur_menu){
    printf_info(DARY_GRAY"-> [%s]\n"COLOR_NONE, cur_menu->text);
    _show_sub_menu(cur_menu);
    printf_info("   "DARY_GRAY"[ 0]"BROWN" back\n");
    printf_info("   "DARY_GRAY"[-1]"BROWN" quit\n");
}




static BOOL _cmp_menu_fn(void *exist, void *data){
    return ((MENU*)exist)->op == *((int*)data);
}

static BOOL _change_menu(MENU **cur_menu, int op){
    // printf("menu[%d]", op);
    if((*cur_menu)->sub_menus == NULL) return FALSE;
    int idx = list_find_idx((*cur_menu)->sub_menus, 0, &op, _cmp_menu_fn);
    if(idx == -1) return FALSE;
    *cur_menu = (MENU*)list_get_elem_by_idx((*cur_menu)->sub_menus, idx);
    // printf("[%s]\n", (*cur_menu)->text);
}

static void _back_menu(MENU *root, MENU **cur_menu){
    int par_id = (*cur_menu)->par_id;
    if(par_id == -1) return;
    *cur_menu = (MENU*)_get_menu_by_id(root, par_id);
}

void show_menu(MENU *root, void *env){
    MENU *cur_menu = root;
    int op;
    char buf[256];
    while(1){
        _show_cur_menu(cur_menu);

        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%d", &op);

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
                printf(DARY_GRAY"-> [%s]\n"COLOR_NONE, cur_menu->text);
                cur_menu->call_fn(cur_menu, env);
                _back_menu(root, &cur_menu);
            }
        }
        else
            printf_error("-> error code, choice again:\n");

    }
}

//////////////////////////////////////////////

void destroy_menu(MENU* root){
    _destroy_menu(root);
    free(root);
}
