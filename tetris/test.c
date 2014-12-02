#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include "utils.h"

void each_type_do(void(*callback)(char type)){
    char *types = "TOILJSZ";
    int i = 0;
    while(types[i]!='\0'){
        callback(types[i]);
        i++;
    }
}

int GLOBAL_PANEL[ROWS][COLS] = {0};


void _draw_view(GAME* game){
    _print_game(game);
}

////////////////////////////////////////
///test_init
////////////////////////////////////////

void test_init_panel(){
    PANEL panel = _init_panel();
    _print_panel(panel);
    free(panel);
}


void test_init_block_callback(char type){
    BLOCK b;
    int i;
    for(i = 0; i < 4; i++) {
        b = _init_block(type, i);
        _print_block(&b);
    }
}
void test_init_block(){
    each_type_do(test_init_block_callback);
}


void test_rand_block(){
    srand(time(NULL));
    BLOCK b;
    int i;
    for(i = 0; i < 10; i++) {
        b = _rand_block();
        _print_block(&b);
    }
}

void test_init_game(){
    GAME* game = init_game(_draw_view);
    _print_game(game);
}

////////////////////////////////////////
///test_move
////////////////////////////////////////

void _test_move(char type, char *direction_str, BOOL(*func)(GAME*) ,int times){
    GAME *game = init_game(_draw_view);

    BLOCK b = _init_block(type, 0);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;

    int i;
    BOOL ret;
    for(i = 1; i <= times; i++){
        ret = func(game);
        printf("%c[%d] %s[%d] %s\n",
            game->cur_block.type, game->cur_block.turn_idx,
            direction_str, i, human_bool(ret));
        if(!ret) break;
    }
}

void test_move_left(char type){
    _test_move(type, "left", move_left, 10);
}

void test_move_right(char type){
    _test_move(type, "right", move_right, 10);
}

void test_move_with_filled(char type){
    GLOBAL_PANEL[1][1] = FILLED;
    _test_move(type, "left", move_left, 20);
}


////////////////////////////////////////
///test_trun
////////////////////////////////////////

void test_turn_block(char type){
    GAME *game = init_game(_draw_view);

    BLOCK b = _init_block(type, 0);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;

    _print_block(&game->cur_block);
    int i, turn_idx;
    BOOL ret;
    for(i = 0; i < 4; i++){
        turn_idx = game->cur_block.turn_idx;
        ret = turn(game);
        printf("%c[%d] turn[%d] %s\n",
            game->cur_block.type, turn_idx, i, human_bool(ret));
        if(!ret) break;
    }
}


void test_turn_block_filled(char type){
    GLOBAL_PANEL[0][5] = FILLED;
    test_turn_block(type);
}


////////////////////////////////////////
///test_move_down
////////////////////////////////////////

void test_panel_be_filled(char type){
    GAME *game = init_game(_draw_view);
    BLOCK b = _init_block(type, 0);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;
    game->draw_view(game);
    _panel_be_filled(game);
    _begin_next_frame(game);
}

void test_check_eliminate(){
    GAME *game = init_game(_draw_view);
    game->panel = (PANEL)GLOBAL_PANEL;

    game->panel[0][5] = FILLED;
    game->panel[6][2] = FILLED;
    int i;
    for(i = 0; i < COLS; i++){
        game->panel[4][i] = FILLED;
        game->panel[5][i] = FILLED;
        game->panel[8][i] = FILLED;
    }
    game->draw_view(game);
    printf("lines = %d\n", _check_eliminate(game));
}


// void test_move_down(char type){
//     _test_move(type, "down", move_down, 20);
// }





int main(int argc, const char* argv[]){

    // test_init_panel();
    // test_init_block();
    // test_rand_block();
    // test_init_game();



    // each_type_do(test_move_left);
    // each_type_do(test_move_right);
    // each_type_do(test_move_with_filled);



    // each_type_do(test_turn_block);
    // each_type_do(test_turn_block_filled);



    // each_type_do(test_panel_be_filled);

    test_check_eliminate();

    // each_type_do(test_move_down);

    return 0;
}

// gcc -I ../utils ../utils/utils.c test.c tetris.c -o test.out -DDEBUG && ./test.out
// gcc -I ../utils ../utils/utils.c test.c tetris.c -o test.out && ./test.out
