#include <stdlib.h>
#include <time.h>
#include <ctrl.h>
#include <view.h>

int main(){
    clear_tty();
    srand(time(NULL));

    int frame_left1 = 25;
    char *cd1[] = {"w","a","d","s","p"};

    GAME_UI *ui1 = ui_init(frame_left1, cd1);
    GAME *game1 = game_init(ui1);
    ui1->game = game1;

    int size = 0;
    PRESS_HANDLER handlers[20];
    bind_press_handlers(game1, cd1, handlers, &size);

    game_begin(game1);
    key_press_loop(handlers, size);
    game_destroy(game1);
    ui_destroy(ui1);

    reset_tty();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_single.c -o tetris_single.out -lm -lpthread -DDEBUG && ./tetris_single.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_single.c -o tetris_single.out -lm -lpthread && ./tetris_single.out
