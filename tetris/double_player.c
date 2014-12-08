#include <stdlib.h>
#include "tetris.h"


int main(){
    clear_tty();
    srand(time(NULL));

    int size = 0;
    PRESS_HANDLER handlers[20];    

    GAME_UI ui1;
    GAME *game1 = game_facade(&ui1, 5, 'w','a','d','s','p', handlers, &size);

    GAME_UI ui2;
    GAME *game2 = game_facade(&ui2, 45, 'i','j','l','k','p', handlers, &size);

    game_begin(game1);
    game_begin(game2);

    key_press_loop(handlers, size);

    game_destroy(game1);
    game_destroy(game2);

    reset_tty();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c double_player.c -o double_player.out -lm -lpthread -DDEBUG && ./double_player.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c double_player.c -o double_player.out -lm -lpthread && ./double_player.out
