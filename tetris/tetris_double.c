#include <stdlib.h>
#include "ctrl.h"


int main(){

    clear_tty();
    srand(time(NULL));

    int frame_left1 = 3;
    char *cd1 = "wadsp";
    int frame_left2 = 42;
    char *cd2 = "ijlkp";

    GAME_UI *ui1 = ui_init(frame_left1, cd1);
    GAME *game1 = game_init(ui1);
    ui1->game = game1;

    GAME_UI *ui2 = ui_init(frame_left2, cd2);
    GAME *game2 = game_init(ui2);
    ui2->game = game2;

    int size = 0;
    PRESS_HANDLER handlers[20];
    bind_press_handlers(game1, cd1, handlers, &size);
    bind_press_handlers(game2, cd2, handlers, &size);

    game_begin(game1);
    game_begin(game2);

    key_press_loop(handlers, size);

    game_destroy(game1);
    game_destroy(game2);

    ui_destroy(ui1);
    ui_destroy(ui2);


    reset_tty();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_double.c -o tetris_double.out -lm -lpthread -DDEBUG && ./tetris_double.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_double.c -o tetris_double.out -lm -lpthread && ./tetris_double.out
