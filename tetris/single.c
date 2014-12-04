#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tetris.h"
#include "view.h"



int frame_left = 5;

void _draw_level_fn(GAME *game){
    draw_level(FRM_TOP, frame_left, game->level);
}

void _draw_score_fn(GAME *game){
    draw_score(FRM_TOP, frame_left, game->score);
}

void _draw_next_fn(GAME *game){
    draw_next_block(FRM_TOP, frame_left, &(game->next_block));
}

void _draw_change_fn(BLOCK *last, GAME *game){
    erase_panel_block(FRM_TOP, frame_left, last); 
    draw_panel_block(FRM_TOP, frame_left, &(game->cur_block));
}

void _draw_panel_fn(GAME *game){
    draw_panel(FRM_TOP, frame_left, game->panel);
}

void _draw_block_fn(GAME *game){
    draw_panel_block(FRM_TOP, frame_left, &(game->cur_block));
}

void _draw_game_over_fn(GAME *game){
    draw_over(FRM_TOP, frame_left);
}



void _timer_hander(void *env){
    move_down((GAME*)env);
}


int main(){
    clear_tty();
    srand(time(NULL));
    draw_frame(FRM_TOP, frame_left, 'w','a','d','s');

    GAME *game = init_game(_draw_level_fn, _draw_score_fn, _draw_next_fn,
        _draw_block_fn, _draw_change_fn, _draw_panel_fn, _draw_game_over_fn);

    SIMPER_TIMER timer;
    timer_new(&timer, 1000, _timer_hander, game);
    timer_start(&timer);

    char ch;
    while((ch = getchar()) != 'q'){
        switch(ch){
            case 'w': turn(game); break;
            case 'a': move_left(game); break;
            case 'd': move_right(game); break;
            case 's': move_down(game); break;
            case 'p': {
                game_pause(game);
                if(game->is_pause)
                    timer_stop(&timer);
                else
                    timer_start(&timer);
            }

        }
        fflush(NULL);
    }
    timer_destroy(&timer);
    destroy_game(game);
    reset_tty();


    return 0;
}






// gcc -I ../utils ../utils/utils.c tetris.c view.c single.c -o single.out -DDEBUG && ./single.out
// gcc -I ../utils ../utils/utils.c tetris.c view.c single.c -o single.out && ./single.out
