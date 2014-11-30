#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    POS_SET pos_set;
    POS_SET base_pos_sets[4];
} BLOCK;

typedef int (*PANEL)[COLS];

typedef struct GAME_TAG{
    int score;
    PANEL panel;
    BLOCK cur_block;
    BLOCK next_block;
    void(*draw_view)(struct GAME_TAG*);
} GAME;

// interface
GAME* init_game(void(*draw_view)(GAME*));
BOOL move_left(GAME *game);
BOOL move_right(GAME *game);
BOOL move_down(GAME *game);
BOOL turn(GAME *game); //means turn left


// for unit test
PANEL _init_panel();
BLOCK _init_block(char type, int turn_idx); //type in "TOILJSZ"
BLOCK _rand_block();
void _print_game(const GAME *game);
void _print_panel(const PANEL panel);
void _print_block(const BLOCK *b);
