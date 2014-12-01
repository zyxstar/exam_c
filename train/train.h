#include "utils.h"
#include "list.h"

typedef struct{
    char name[20]; //char array, need't free
    float price;
} STATION;

typedef struct{
    char no[10];
    LIST *stations;
} TRAIN;

LIST* init_trains();
void destroy_trains(LIST *trains);

TRAIN* add_train(LIST *trains, char *no);
BOOL add_station(TRAIN *train, char *name, float price);

TRAIN* find_train_by_no(LIST *trains, char *no);
STATION* find_station_by_name(TRAIN *train, char *name);
int find_trains_by_station(LIST *trains, char *start_station, char *end_station, void(*process)(TRAIN*, char*, char*));

void list_trains(LIST *trains);
void list_train(TRAIN *train);
void list_choice_train(TRAIN *train, char *start_station, char *end_station);

void save_trains(LIST *trains, FILE* fp);
LIST* load_trains(FILE* fp);

