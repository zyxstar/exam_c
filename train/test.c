#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "list.h"
#include "user.h"
#include "train.h"

void test_user(){
    LIST *user_list = init_users();
    printf("reg: %s\n", human_bool(register_user(user_list,"abc","123")));
    printf("reg: %s\n", human_bool(register_user(user_list,"def","123")));
    printf("reg: %s\n", human_bool(register_user(user_list,"abc","123")));

    list_users(user_list);

    printf("login: %p\n", validate_user(user_list,"abc","123"));
    printf("login: %p\n", validate_user(user_list,"abc","124"));

    destroy_users(user_list);
}

void test_train(){
    LIST *train_list = init_trains();
    TRAIN *train = NULL;

    train = add_train(train_list, "No_01");
    printf("add_train: %p\n", train);

    printf("add_station: %s\n", human_bool(add_station(train, "BJ", 0.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "TJ", 20.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "SH", 50.0)));

    train = add_train(train_list, "No_02");
    printf("add_train: %p\n", train);

    printf("add_station: %s\n", human_bool(add_station(train, "BJ", 0.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "BJ", 1.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "HB", 20.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "WH", 50.0)));

    train = add_train(train_list, "No_02");
    printf("add_train: %p\n", train);

    train = add_train(train_list, "No_03");
    printf("add_train: %p\n", train);

    printf("add_station: %s\n", human_bool(add_station(train, "BJ", 0.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "TJ", 20.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "HB", 30.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "SH", 60.0)));
    printf("add_station: %s\n", human_bool(add_station(train, "WH", 50.0)));


    list_trains(train_list);

    train = find_train_by_no(train_list, "No_02");
    printf("add_train: %p\n", train);
    list_train(train);

    printf("TJ-SH: \n");
    find_trains_by_station(train_list, "TJ", "SH", list_choice_train);

    printf("HB-WH: \n");
    find_trains_by_station(train_list, "HB", "WH", list_choice_train);

    destroy_trains(train_list);
}


int main(){
    test_user();
    test_train();

    return 0;
}

// gcc utils.c list.c user.c train.c test.c -o test.out -DDEBUG && ./test.out
// gcc utils.c list.c user.c train.c test.c -o test.out && ./test.out
