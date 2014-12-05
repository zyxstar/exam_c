#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "game.h"
#include "view.h"

void _draw_level_fn(GAME_UI *ui){
    draw_level(FRM_TOP, ui->frame_left, ui->game->level);
}

void _draw_score_fn(GAME_UI *ui){
    draw_score(FRM_TOP, ui->frame_left, ui->game->score);
}

void _draw_next_fn(GAME_UI *ui){
    draw_next_block(FRM_TOP, ui->frame_left, &ui->game->next_block);
}

void _draw_change_fn(BLOCK *last, GAME_UI *ui){
    erase_panel_block(FRM_TOP, ui->frame_left, last);
    draw_panel_block(FRM_TOP, ui->frame_left, &ui->game->cur_block);
}

void _draw_panel_fn(GAME_UI *ui){
    draw_panel(FRM_TOP, ui->frame_left, ui->game->panel);
}

void _draw_block_fn(GAME_UI *ui){
    draw_panel_block(FRM_TOP, ui->frame_left, &ui->game->cur_block);
}

void _draw_game_over_fn(GAME_UI *ui){
    draw_over(FRM_TOP, ui->frame_left);
}

void _draw_pause_fn(GAME_UI *ui){
    draw_pause(FRM_TOP, ui->frame_left);
}

void _draw_running_fn(GAME_UI *ui){
    draw_running(FRM_TOP, ui->frame_left);
}

void build_game(int frame_left, char turn_cd, char left_cd, char right_cd, char down_cd){

    draw_frame(FRM_TOP, frame_left, turn_cd, left_cd, right_cd, down_cd);

    GAME_UI ui;
    GAME *game = game_init(&ui);
    ui.game = game;
    ui.frame_left = frame_left;
    ui.draw_level = _draw_level_fn;
    ui.draw_score = _draw_score_fn;
    ui.draw_next = _draw_next_fn;
    ui.draw_block = _draw_block_fn;
    ui.draw_change = _draw_change_fn;
    ui.draw_panel = _draw_panel_fn;
    ui.draw_pause = _draw_pause_fn;
    ui.draw_running = _draw_running_fn;
    ui.draw_game_over = _draw_game_over_fn;

    game_begin(game);

    char ch;
    while((ch = getchar()) != 'q'){
        switch(ch){
            case 'w': {
                game_turn(game);
                break;
            }
            case 'a': {
                game_move_left(game);
                break;
            }
            case 'd': {
                game_move_right(game);
                break;
            }
            case 's': {
                game_move_down(game);
                break;
            }
            case 'p':{
                game_pause(game);
                break;
            }

        }
        fflush(NULL);
    }

    game_destroy(game);

}




int main(){
    clear_tty();
    srand(time(NULL));

    build_game(5, 'w','a','d','s');

    reset_tty();
    return 0;
}






// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c -o tetris.out -DDEBUG -lpthread && ./tetris.out 2>>debug.log

// gcc -I ../utils ../utils/utils.c game.c view.c tetris.c -o tetris.out -lpthread && ./tetris.out
