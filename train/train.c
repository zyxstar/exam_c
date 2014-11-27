#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"


static void _destroy_train(void *data){
    TRAIN *train = (TRAIN*)data;
    DEBUG_WRITE(("  # _destroy_train: [no]%s, [stations]%p, [size]%d\n",
        train->no, train->stations, train->stations->used_len));
    list_free(train->stations);
    free(train->stations);
}

LIST* init_trains(){
    LIST *trains = malloc(sizeof(LIST));
    list_new(trains, sizeof(TRAIN), _destroy_train); //need free
    return trains;
}

void destroy_trains(LIST *trains){
    list_free(trains);
    free(trains);
}

static BOOL _cmp_train(void *exist, void *data){
    TRAIN *e = (TRAIN*)exist;
    TRAIN *d = (TRAIN*)data;
    return strcmp(e->no, d->no) == 0;
}

TRAIN* add_train(LIST *trains, char *no){
    TRAIN nt = {0};
    strcpy(nt.no, no);
    TRAIN *ret =(TRAIN*)list_add_unique_elem(trains, &nt, _cmp_train);
    if(ret != NULL){// init stations when successful
        ret->stations = malloc(sizeof(LIST));
        list_new(ret->stations, sizeof(STATION), NULL); //need't free
    }
    return ret;
}

static BOOL _cmp_station(void *exist, void *data){
    STATION *e = (STATION*)exist;
    STATION *d = (STATION*)data;
    return strcmp(e->name, d->name) == 0;
}

BOOL add_station(TRAIN *train, char *name, float price){
    STATION ns = {0};
    strcpy(ns.name, name);
    ns.price = price;
    return list_add_unique_elem(train->stations, &ns, _cmp_station) != NULL;
}

TRAIN* find_train_by_no(LIST *trains, char *no){
    TRAIN t;
    strcpy(t.no, no);
    int idx = list_find_idx(trains, 0, &t, _cmp_train);
    if(idx == -1) return NULL;
    return (TRAIN*)list_get_elem_by_idx(trains, idx);
}

STATION* find_station_by_name(TRAIN *train, char *name){
    STATION s;
    strcpy(s.name, name);
    int idx = list_find_idx(train->stations, 0, &s, _cmp_station);
    if(idx == -1) return NULL;
    return (STATION*)list_get_elem_by_idx(train->stations, idx);
}

static void _print_train(void *data, int idx, void *extra){
    TRAIN *t = (TRAIN*)data;
    printf("[%2d] ", idx);
    list_train(t);
}

static BOOL _choice_train(void *exist, void *extra){
    TRAIN *train = (TRAIN*)exist;
    char **choice_stations = (char**)extra;
    return find_station_by_name(train, choice_stations[0]) != NULL &&
        find_station_by_name(train, choice_stations[1]) != NULL;
}

int find_trains_by_station(LIST *trains, char *start_station, char *end_station, void(*process)(TRAIN*, char*, char*)){
    char *choice_stations[] = {strdup(start_station), strdup(end_station)};
    int idx = -1, count = 0;
    TRAIN *train;
    while((idx = list_find_idx(trains, idx+1, choice_stations, _choice_train)) != -1){
        count++;
        train = (TRAIN*)list_get_elem_by_idx(trains, idx);
        process(train, start_station, end_station);
    }

    free(choice_stations[0]);
    free(choice_stations[1]);
    return count;
}

void list_trains(LIST *trains){
    list_each_elem_do(trains, NULL, _print_train);
}

static void _print_station(void *data, int idx, void *extra){
    STATION *s = (STATION*)data;
    printf("    [%2d] station: %-10s price: %.2f\n", idx, s->name, s->price);
}

void list_train(TRAIN *train){
    printf(" train_no: %-10s stations: %d\n", train->no, train->stations->used_len);
    list_each_elem_do(train->stations, NULL, _print_station);
}

void list_choice_train(TRAIN *train, char *start_station, char *end_station){
    STATION *s1 = find_station_by_name(train, start_station);
    STATION *s2 = find_station_by_name(train, end_station);
    printf("begin: %-10s end: %-10s ticket_price: %.2f\n", start_station, end_station, s2->price - s1->price);
    printf(" train_no: %-10s stations: %d\n", train->no, train->stations->used_len);

    STATION s;
    strcpy(s.name, start_station);
    int idx1 = list_find_idx(train->stations, 0, &s, _cmp_station);
    strcpy(s.name, end_station);
    int idx2 = list_find_idx(train->stations, 0, &s, _cmp_station);
    for(; idx1 <= idx2; idx1++)
        _print_station(list_get_elem_by_idx(train->stations, idx1), idx1, NULL);
}

