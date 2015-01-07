#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "list.h"

typedef void reduce_call1(int *, int *, int);
void _reduce1(reduce_call1 *, int *arr, int size, int *stat);
def_reduce(_reduce1, int, int);

void add(int *acc, int *b, int idx){ *acc += *b;}
void test_reduce1(){
    int arr[] = {1,3,4,56};
    int stat = 0;
    _reduce1(add, arr, arr_len(arr), &stat);
    printf("%d\n",stat);

}


struct stat_char{
    char ch;
    int idx;
};
def_reduce(_reduce2, char, struct stat_char);
void get_max(struct stat_char *acc, char *ch, int idx){
    if(*ch > acc->ch){
        acc->ch = *ch;
        acc->idx = idx;
    }
}
void test_reduce2(){
    char *name = "abcjdeg";
    struct stat_char stat = {0,-1};
    _reduce2(get_max, name, strlen(name), &stat);
    printf("max: %c:%d\n", stat.ch, stat.idx);
}


struct student{
    char name[20];
    int score;
};
def_reduce(_reduce3, struct student, int);
void get_sum(int *acc, struct student *stu, int idx){
    *acc += stu->score;
}
void test_reduce3(){
    LIST stus;
    list_new(&stus, sizeof(struct student), NULL);
    struct student tmp;
    int i;
    for(i = 0; i<10; i++){
        strcpy(tmp.name, "abc");
        tmp.score = i+10;
        list_add_elem(&stus, &tmp);
    }
    int sum = 0;
    _reduce3(get_sum, stus.header, stus.used_len, &sum);
    printf("sum: %d\n",sum);
    list_free(&stus);

}

void calc(int *acc, int *b, int idx){
    static int base;
    if(idx == -1){
        base = 100;
        return;
    }
    *acc += base + *b;
}
void test_reduce4(){
    int arr[] = {1,3,4,56};
    int stat = 0;
    calc(NULL, NULL, -1); //set env
    _reduce1(calc, arr, arr_len(arr), &stat);
    printf("%d\n",stat);
}


def_each(_each1, int);
void print_int(int *data, int idx){
    printf("[%d]%d\n", idx, *data);
}
void test_each(){
    int arr[] = {1,3,4,56};
    _each1(print_int, arr, arr_len(arr));
}


void test_range1(){
    int arr[10];
    int size = range(1, 9, 1, arr);
    _each1(print_int, arr, size);
}

void test_range2(){
    int arr[10];
    int size = range(9, 2, -2, arr);
    _each1(print_int, arr, size);
}

void print_char(int *data, int idx){
    printf("[%d]%c\n", idx, *data);
}
void test_range3(){
    int arr[10];
    int size = range('a', 'z', 3, arr);
    _each1(print_char, arr, size);
}


def_map(_map1, int, struct student);
void gen_stu(int *src, struct student* dest, int idx){
    strcpy(dest->name, "abc");
    dest->score = 100 - *src;
}

def_each(_each2, struct student);
void print_stu(struct student *stu, int idx){
    printf("[%d] %s %d\n", idx, stu->name, stu->score);
}

void test_map1(){
    int arr[] = {1,3,4,56};
    struct student* stus = _map1(gen_stu, arr, arr_len(arr));
    _each2(print_stu, stus, arr_len(arr));
    free(stus);
}


def_map(_map2, int, struct student*);
void gen_stu2(int *src, struct student** dest, int idx){
    *dest = malloc(sizeof(struct student));
    strcpy((*dest)->name, "abc");
    (*dest)->score = 100 - *src;
}

def_each(_each3, struct student*);
void print_stu_and_free(struct student **stu, int idx){
    printf("[%d] %s %d\n", idx, (*stu)->name, (*stu)->score);
    free(*stu);
}


void test_map2(){
    int arr[] = {1,3,4,56};
    struct student** stus = _map2(gen_stu2, arr, arr_len(arr));
    _each3(print_stu_and_free, stus, arr_len(arr));
    free(stus);
}


def_filter(_filter1, int);
int predicate1(int *data, int idx){
    return *data % 2 == 0;
}

def_map(_map3, int*, int);
void trans(int **src, int *dest, int idx){
    *dest = **src;
}

void test_filter1(){
    int arr[] = {1,3,4,7,9,12,16};
    int found;
    int **ret = _filter1(predicate1, arr, arr_len(arr), &found);
    int i;
    printf("count %d\n", found);
    for(i = 0; i < found; i++){
        printf("%d\n", *(ret[i]));
    }

    int *int_arr = _map3(trans, ret, found); // int** to int*
    _each1(print_int, int_arr, found);
    free(ret);
    free(int_arr);
}




int main(){
    test_reduce1();
    // test_reduce2();
    // test_reduce3();
    // test_reduce4();
    // test_each();
    // test_range1();
    // test_range2();
    // test_range3();
    // test_map1();
    // test_map2();
    // test_filter1();
    return 0;
}


// gcc list.c test_array.c -o test_array.out && ./test_array.out
