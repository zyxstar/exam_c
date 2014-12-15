#include "filter.h"
#include <stdio.h>
#include <string.h>


struct stat{
    char ch;
    int idx;
};

def_reduce(_reduce1, int, int);

_reduce2 = def_reduce(char, struct stat);

void add(int *acc, int b, int idx){ *acc += b;}

void get_max(struct stat *acc, char ch, int idx){
    if(ch > acc->ch){
        acc->ch = ch;
        acc->idx = idx;
    }
}



int main(){
    int arr[] = {1,3,4,56};
    int stat1 = 0;
    _reduce1(add, arr, 4, &stat1);
    printf("%d\n",stat1);

    char *name = "abcjdeg";
    struct stat stat2 = {0,-1};
    _reduce2(get_max, name, strlen(name), &stat2);
    printf("%c:%d\n", stat2.ch, stat2.idx);

    return 0;
}
