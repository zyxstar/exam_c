#ifndef TETRIS_H_INCLUEDE
#define TETRIS_H_INCLUEDE

#include "utils.h"

#define ROWS 16
#define COLS 10

typedef enum{
    EMPTY,
    FILLED
} POS_STAT;

typedef struct{
    int x; //index with column
    int y; //index with row
} POS;

typedef struct{
    POS pos0;
    POS pos1;
    POS pos2;
    POS pos3;
} POS_SET;

typedef struct{
    char type;
    int turn_idx;
    int down_count;
    POS_SET pos_set;
    POS_SET base_pos_sets[4];
} BLOCK;

typedef int (*PANEL)[COLS];

typedef struct GAME_TAG{
    int score;
    PANEL panel;
    BLOCK cur_block;
    BLOCK next_block;
    void(*_origin_draw_view)(struct GAME_TAG*);
    void(*draw_view)(struct GAME_TAG*);
    void(*draw_game_over)(struct GAME_TAG*);
} GAME;

// interface
GAME* init_game(void(*draw_view)(GAME*));
BOOL move_left(GAME *game);
BOOL move_right(GAME *game);
BOOL move_down(GAME *game);
BOOL turn(GAME *game); //means turn left

void game_begin(GAME *game);
void game_pause(GAME *game);
void game_over(GAME *game);


// for unit test
PANEL _init_panel();
BLOCK _init_block(char type, int turn_idx); //type in "TOILJSZ"
BLOCK _rand_block();

void _panel_be_filled(GAME *game);
void _begin_next_frame(GAME *game);
int _check_eliminate(GAME *game);


void _print_game(GAME *game);
void _print_panel(PANEL panel);
void _print_block(BLOCK *b);


#endif /*TETRIS_H_INCLUEDE*/
