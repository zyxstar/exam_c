#include <stdlib.h>
#include "ctrl.h"

// char _store_ch(char ch){ //stack
//     static char buffer[10];
//     static int bufp = 0;
//     if(0 == ch){//get
//         if(0 == bufp) return 0;
//         return buffer[--bufp];
//     }
//     buffer[bufp++] = ch; //set
//     return 0;
// }

// char _get_char(){
//     return _store_ch(0);
// }

// void _set_char(char ch){
//     _store_ch(ch);
// }

void key_press_loop2(GAME *game){
    char ch;
    while((ch = getchar()) != 'q'){
        if(ch == 'p'){
            game_pause(game);
            continue;
        }
        if(ch != 27) continue;
        if(getchar() != 91) continue;

        switch(getchar()){
            case 65: game_turn(game); break;
            case 68: game_move_left(game); break;
            case 67: game_move_right(game); break;
            case 66: game_move_down(game); break;
        }
    }
}


int main(){
    clear_tty();
    srand(time(NULL));

    int frame_left1 = 25;
    char *cd1[] = {"↑","←","→","↓","p"};

    GAME_UI *ui1 = ui_init(frame_left1, cd1);
    GAME *game1 = game_init(ui1);
    ui1->game = game1;

    game_begin(game1);

    key_press_loop2(game1);

    game_destroy(game1);
    ui_destroy(ui1);

    reset_tty();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_single2.c -o tetris_single2.out -lm -lpthread -DDEBUG && ./tetris_single2.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c ctrl.c tetris_single2.c -o tetris_single2.out -lm -lpthread && ./tetris_single2.out
