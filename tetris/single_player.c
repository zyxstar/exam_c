#include <stdlib.h>
#include "tetris.h"


int main(){
    clear_tty();
    srand(time(NULL));

    int size = 0;
    PRESS_HANDLER handlers[20];

    GAME_UI ui1;
    GAME *game1 = game_facade(&ui1, 15, 'w','a','d','s','p', handlers, &size);

    game_begin(game1);
    key_press_loop(handlers, size);
    timer_destroy(&ui1.timer);
    game_destroy(game1);

    reset_tty();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c single_player.c -o single_player.out -lm -lpthread -DDEBUG && ./single_player.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c single_player.c -o single_player.out -lm -lpthread && ./single_player.out
