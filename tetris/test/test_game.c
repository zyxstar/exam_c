#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "game.h"

////////////////////////////////////////
///test_helper
////////////////////////////////////////

void _print_panel(PANEL panel){
    int row, col;
    printf("PANEL: 0123456789\n");
    for(row = 0; row < ROWS; row++){
        printf("       ");
        for(col = 0; col < COLS; col++){
            printf("%c", panel[row][col] == FILLED ? 'O' : '_');
        }
        printf(" %d\n", row);
    }
}


void _print_block(BLOCK *b){
    printf("%c[%d][%d]", b->type, b->turn_idx, b->down_count);
    printf("{{%d,%d},{%d,%d},{%d,%d},{%d,%d}}\n",
            b->pos_set.pos0.x, b->pos_set.pos0.y,
            b->pos_set.pos1.x, b->pos_set.pos1.y,
            b->pos_set.pos2.x, b->pos_set.pos2.y,
            b->pos_set.pos3.x, b->pos_set.pos3.y);

    int row, col;
    printf("       0123456789\n");
    for(row = 0; row < ROWS; row++){
        printf("    %2d ", row);
        for(col = 0; col < COLS; col++){
            if((b->pos_set.pos0.x == col && b->pos_set.pos0.y == row) ||
               (b->pos_set.pos1.x == col && b->pos_set.pos1.y == row) ||
               (b->pos_set.pos2.x == col && b->pos_set.pos2.y == row) ||
               (b->pos_set.pos3.x == col && b->pos_set.pos3.y == row))
                printf("#");
            else
                printf("_");
        }
        printf("\n");
    }
}

void _print_game(GAME *game){
    printf("\nGAME: [sroce]%d, [ui]%p, [next]%c%d\n", game->score, game->ui, game->next_block.type, game->next_block.turn_idx);
    _print_block(&game->cur_block);
    _print_panel(game->panel);
}





void each_type_do(void(*callback)(char type)){
    char *types = "TOILJSZ";
    int i = 0;
    while(types[i]!='\0'){
        callback(types[i]);
        i++;
    }
}

int GLOBAL_PANEL[ROWS][COLS] = {0};




void _draw_view(GAME_UI *ui){
    _print_game(ui->game);
}
void _draw_change(BLOCK *last, GAME_UI *ui){
    _print_game(ui->game);
}

GAME_UI ui={0, {0}, 0, NULL, _draw_view, _draw_view, _draw_view, _draw_view,
      _draw_change, _draw_view, _draw_view, _draw_view, _draw_view};

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
    GAME* game = game_init(&ui);
    _print_game(game);
}

////////////////////////////////////////
///test_move
////////////////////////////////////////

void _test_move(char type, char *direction_str, BOOL(*func)(GAME*) ,int times){
    GAME *game = game_init(&ui);
    ui.game = game;
    BLOCK b = _init_block(type, 0);
    timer_destroy(&game->timer);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;

    int i;
    BOOL ret;
    for(i = 1; i <= times; i++){
        b = game->cur_block;
        ret = func(game);
        printf("%c[%d] %s[%d] %s\n",
            b.type, b.turn_idx,
            direction_str, i, human_bool(ret));
        if(!ret) break;
    }
}

void test_move_left(char type){
    _test_move(type, "left", game_move_left, 10);
}

void test_move_right(char type){
    _test_move(type, "right", game_move_right, 10);
}

void test_move_with_filled(char type){
    GLOBAL_PANEL[1][1] = FILLED;
    _test_move(type, "left",game_move_left, 20);
}


////////////////////////////////////////
///test_trun
////////////////////////////////////////

void test_turn_block(char type){
    GAME *game = game_init(&ui);
    ui.game = game;
    BLOCK b = _init_block(type, 0);
    timer_destroy(&game->timer);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;

    _print_block(&game->cur_block);
    int i, turn_idx;
    BOOL ret;
    for(i = 0; i < 4; i++){
        turn_idx = game->cur_block.turn_idx;
        ret = game_turn(game);
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
    GAME *game = game_init(&ui);
    ui.game = game;
    BLOCK b = _init_block(type, 0);
    timer_destroy(&game->timer);
    game->cur_block = b;
    game->panel = (PANEL)GLOBAL_PANEL;

    // _print_game(game);
    _panel_be_filled(game);
    // _begin_next(game);
}

void test_check_eliminate(){
    GAME *game = game_init(&ui);
    ui.game = game;
    timer_destroy(&game->timer);
    game->panel = (PANEL)GLOBAL_PANEL;

    game->panel[0][5] = FILLED;
    game->panel[6][2] = FILLED;
    int i;
    for(i = 0; i < COLS; i++){
        game->panel[4][i] = FILLED;
        game->panel[5][i] = FILLED;
        game->panel[8][i] = FILLED;
    }
    _print_game(game);
    _check_eliminate(game);
}


void test_move_down(char type){
    _test_move(type, "down", game_move_down, 21);
}


void test_move_turn(){
    GAME *game = game_init(&ui);
    ui.game = game;
    timer_destroy(&game->timer);
    BLOCK b = _init_block('T', 0);
    game->cur_block = b;

    game_move_down(game);
    game_move_left(game);
    game_move_left(game);
    game_move_left(game);
    game_move_left(game);
    game_turn(game);

}

void test_game_over(){
    GAME *game = game_init(&ui);
    ui.game = game;
    timer_destroy(&game->timer);
    int i;
    for(i = 0; i < 100; i++)
        game_move_down(game);
}


int main(int argc, const char* argv[]){

    // test_init_panel();
    // test_init_block();
    // test_rand_block();
    // test_init_game();


    each_type_do(test_move_left);
    // each_type_do(test_move_right);
    // each_type_do(test_move_with_filled);



    // each_type_do(test_turn_block);
    // each_type_do(test_turn_block_filled);



    // each_type_do(test_panel_be_filled);

    // test_check_eliminate();

    // each_type_do(test_move_down);

    // test_move_turn();

    // test_game_over();


    return 0;
}

// gcc -I../../utils -I../ ../../utils/console.c ../../utils/simple_timer.c test_game.c ../game.c -o test_game.out -DDEBUG -lm && ./test_game.out
// gcc -I../../utils -I../ ../../utils/console.c ../../utils/simple_timer.c test_game.c ../game.c -o test_game.out -DDEBUG -lm && ./test_game.out 2> test.log
