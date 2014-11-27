#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "list.h"
#include "user.h"
#include "train.h"
#include "menu.h"


// ui logic
void register_user_ui(MENU *cur_menu, void *env){
    LIST *user_list = (LIST*)((void**)env)[0];
    char name[10], passwd[10];
    printf("enter username: ");
    scanf("%s", name);
    printf("enter password: ");
    scanf("%s", passwd);
    if(register_user(user_list,name,passwd))
        printf_correct("resigter successful\n");
    else
        printf_error("resigter failed: user exist\n");
}

void validate_user_ui(MENU *cur_menu, void *env){
    LIST *user_list = (LIST*)((void**)env)[0];
    USER **cur_user = (USER**)((void**)env)[2];
    char name[10], passwd[10];
    printf("enter username: ");
    scanf("%s", name);
    printf("enter password: ");
    scanf("%s", passwd);
    *cur_user = validate_user(user_list,name,passwd);
    if(*cur_user != NULL)
        printf_correct("login successful\n");
    else
        printf_error("login failed\n");
}

void list_users_ui(MENU *cur_menu, void *env){
    LIST *user_list = (LIST*)((void**)env)[0];
    list_users(user_list);
}

void add_train_ui(MENU *cur_menu, void *env){
    LIST *train_list = (LIST*)((void**)env)[1];
    char no[10];
    printf("enter train no: ");
    scanf("%s", no);
    if(add_train(train_list,no)!=NULL)
        printf_correct("add train successful\n");
    else
        printf_error("add train failed: train exist\n");

}

void add_stations_ui(MENU *cur_menu, void *env){
    LIST *train_list = (LIST*)((void**)env)[1];
    char no[10], name[10];
    float price;
    printf("enter train no: ");
    scanf("%s", no);
    TRAIN *train = find_train_by_no(train_list, no);
    if(train == NULL){
        printf_error("wrong train no\n");
        return;
    }
    while(1){
        printf("enter station name(enter \"EOF\" if finished): ");
        scanf("%s", name);
        if(strcmp(name, "EOF") == 0) break;

        printf("enter station price: ");
        scanf("%f", &price);
        if(add_station(train, name, price))
            printf_correct("add station successful\n");
        else
            printf_error("add station failed: station exist\n");
    }
}

void list_all_trains_ui(MENU *cur_menu, void *env){
    LIST *train_list = (LIST*)((void**)env)[1];
    list_trains(train_list);
}

void query_train_no_ui(MENU *cur_menu, void *env){
    LIST *train_list = (LIST*)((void**)env)[1];
    char no[10];
    printf("enter train no: ");
    scanf("%s", no);
    TRAIN *train = find_train_by_no(train_list, no);
    if(train == NULL){
        printf_error("wrong train no\n");
        return;
    }
    list_train(train);
}

void query_stations_ui(MENU *cur_menu, void *env){
    LIST *train_list = (LIST*)((void**)env)[1];
    char begin[10], end[10];
    printf("enter begin station name: ");
    scanf("%s", begin);
    printf("enter end station name: ");
    scanf("%s", end);
    int count = find_trains_by_station(train_list, begin, end, list_choice_train);
    printf("results count: %d\n", count);
}

void book_ticket_ui(MENU *cur_menu, void *env){
    USER **cur_user = (USER**)((void**)env)[2];
    *cur_user = validate_user(user_list,name,passwd);
    if(*cur_user == NULL){
        printf_error("current user is null, please login\n");
        return;
    }
    printf_correct("current user is %s\n", *cur_user->name);
    // book ticket ...
}

// menu config
void prepare_menus(MENU *menus){
    insert_menu(menus, 1, 0, 1, "manage users", NULL);
      insert_menu(menus, 11, 1, 11, "register", register_user_ui);
      insert_menu(menus, 13, 1, 13, "list users", list_users_ui);

    insert_menu(menus, 2, 0, 2, "user login", validate_user_ui);

    insert_menu(menus, 3, 0, 3, "manage trains", NULL);
      insert_menu(menus, 31, 3, 31, "add train", add_train_ui);
      insert_menu(menus, 32, 3, 32, "add stations", add_stations_ui);
      insert_menu(menus, 33, 3, 33, "list all trains", list_all_trains_ui);

    insert_menu(menus, 4, 0, 4, "query trains", NULL);
      insert_menu(menus, 41, 4, 41, "query by train no", query_train_no_ui);
      insert_menu(menus, 42, 4, 42, "query by stations", query_stations_ui);

    insert_menu(menus, 5, 0, 5, "manage tickets", NULL);
      insert_menu(menus, 51, 5, 51, "query tickets", NULL);
      insert_menu(menus, 52, 5, 52, "book ticket", book_ticket_ui);

}



// app
int main(){
    LIST *user_list = init_users();
    LIST *train_list = init_trains();
    MENU *root = init_menu();
    USER *cur_user = NULL;

    prepare_menus(root);
    void *env[] = {user_list, train_list, cur_user};
    show_menu(root, env);

    destroy_users(user_list);
    destroy_trains(train_list);
    destroy_menu(root);

    return 0;
}



// gcc utils.c list.c user.c train.c menu.c app.c -o app.out -DDEBUG && ./app.out
// gcc utils.c list.c user.c train.c menu.c app.c -o app.out && ./app.out
