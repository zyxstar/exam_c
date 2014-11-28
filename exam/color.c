#include <stdio.h>
#include "utils.h"


int main(){
    int i,j;
    for(i = 30; i<39; i++){
        printf("\033[0m\033[0;%dmCOLOR COLOR 0;%d\033[0m\n", i,i);
        printf("\033[0m\033[1;%dmCOLOR COLOR 1;%d\033[0m\n", i,i);
        printf("\033[0m\033[2;%dmCOLOR COLOR 2;%d\033[0m\n", i,i);
        // printf("\033[0m\033[4;%dmCOLOR COLOR 4;%d\033[0m\n", i,i);
        // printf("\033[0m\033[5;%dmCOLOR COLOR 5;%d\033[0m\n", i,i);
        // printf("\033[0m\033[7;%dmCOLOR COLOR 7;%d\033[0m\n", i,i);
        // printf("\033[0m\033[8;%dmCOLOR COLOR 8;%d\033[0m\n", i,i);


        // for(j = 40; j<50; j++){

        // printf("  \033[0m\033[0;%d;%dmCOLOR COLOR 0;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[1;%d;%dmCOLOR COLOR 1;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[2;%d;%dmCOLOR COLOR 2;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[4;%d;%dmCOLOR COLOR 4;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[5;%d;%dmCOLOR COLOR 5;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[7;%d;%dmCOLOR COLOR 7;%d;%d\033[0m\n",j, i,j,i);
        // printf("  \033[0m\033[8;%d;%dmCOLOR COLOR 8;%d;%d\033[0m\n",j, i,j,i);


        // }
    }

printf( VT_BLACK_LIGHT VT_BG_RED VT_UNDTER"%s"VT_BG_NONE"DDDD"VT_RESET"\n", "TEST");


    return 0;
}

// gcc -I ../utils color.c -o color.out && ./color.out
