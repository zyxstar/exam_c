#include <stdio.h>
#include "utils.h"


int main(){
    int i,j;
    for(i = 30; i<39; i++){
        printf("\033[0m\033[0;%dmCOLOR 0;%d\033[0m", i,i);
        printf("\t\033[0m\033[1;%dmCOLOR 1;%d\033[0m", i,i);
        printf("\t\033[0m\033[2;%dmCOLOR 2;%d\033[0m", i,i);
        printf("\t\033[0m\033[4;%dmCOLOR 4;%d\033[0m", i,i);
        printf("\t\033[0m\033[7;%dmCOLOR 7;%d\033[0m\n", i,i);

        for(j = 40; j<47; j++){
            printf("\t\033[0m\033[0;%d;%dmCOLOR 0;%d;%d\033[0m",j, i,j,i);
            printf("\t\033[0m\033[1;%d;%dmCOLOR 1;%d;%d\033[0m",j, i,j,i);
            printf("\t\033[0m\033[2;%d;%dmCOLOR 2;%d;%d\033[0m",j, i,j,i);
            printf("\t\033[0m\033[4;%d;%dmCOLOR 4;%d;%d\033[0m",j, i,j,i);
            printf("\t\033[0m\033[7;%d;%dmCOLOR 7;%d;%d\033[0m\n",j, i,j,i);
        }
    }

    return 0;
}

// gcc -I ../ test_vt_color.c -o test_vt_color.out && ./test_vt_color.out
