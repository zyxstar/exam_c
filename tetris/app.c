#include <stdio.h>
#include <stdlib.h>
#include "utils.h"




int main(int argc, const char* argv[]){
set_keypress();
    char ch;
    while((ch = getchar()) != 'q'){
        printf("=%d ", ch);
        fflush(NULL);
    }
    reset_keypress();

    return 0;
}


// gcc -I ../utils ../utils/utils.c app.c -o app.out && ./app.out
// gcc -I ../utils ../utils/utils.c tetris.c view.c app.c -o app.out && ./app.out
