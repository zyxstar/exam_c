#include "utils.h"
#include "list.h"

typedef struct{
    char *name; //char pointer, need free
    char *passwd;
} USER;

BOOL register_user(LIST *users, char *name, char *passwd);
USER* validate_user(LIST *users, char *name, char *passwd);
void list_users(LIST *users);
void destroy_users(LIST *users);


typedef struct{
    char name[20]; //char array, need't free
    float price;
} STATION;

typedef struct{
    char no[10];
    LIST *stations;
} TRAIN;


TRAIN* add_train(LIST *trains, char *no);
BOOL add_station(TRAIN *train, char *name, float price);
TRAIN* find_train_by_no(LIST *trains, char *no);
STATION* find_station_by_name(TRAIN *train, char *name);
void list_trains(LIST *trains);
void list_train(TRAIN *train);
void list_choice_train(TRAIN *train, char *start_station, char *end_station);
void find_train_by_station(LIST *trains, char *start_station, char *end_station, void(*process)(TRAIN*, char*, char*));

void destroy_trains(LIST *trains);

