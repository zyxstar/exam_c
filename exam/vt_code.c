#include <stdio.h>
#include "utils.h"


int main(){
    int i;
    // printf("\033[2J\n");
    // printf("\033[s\n");



    // printf("\033[10;20H\n");

    // scanf("%d", &i);

    // printf("\033[u\n");


    printf("\033[2A\n");
    printf("\033[K\n");

    return 0;
}

// gcc -I ../utils vt_code.c -o vt_code.out && ./vt_code.out
