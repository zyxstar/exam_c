#ifndef TETRIS_H_INCLUEDE
#define TETRIS_H_INCLUEDE

#include "utils.h"

#define ROWS 20
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
    int level;
    int timer_interval;
    int timer_interval_bak;
    BOOL is_over;
    BOOL is_pause;
    PANEL panel;
    BLOCK cur_block;
    BLOCK next_block;

    void(*draw_level)(struct GAME_TAG*);
    void(*draw_score)(struct GAME_TAG*);
    void(*draw_next)(struct GAME_TAG*);

    void(*draw_block)(struct GAME_TAG*);
    void(*draw_change)(BLOCK *last, struct GAME_TAG*);
    void(*draw_panel)(struct GAME_TAG*);
    void(*draw_game_over)(struct GAME_TAG*);

} GAME;

// interface
GAME* init_game(void(*draw_level)(GAME*), void(*draw_score)(GAME*), void(*draw_next)(GAME*),
     void(*draw_block)(GAME*),void(*draw_change)(BLOCK*, GAME*), void(*draw_panel)(GAME*), void(*draw_game_over)(GAME*));
BOOL move_left(GAME *game);
BOOL move_right(GAME *game);
BOOL move_down(GAME *game);
BOOL turn(GAME *game); //means turn left

void game_begin(GAME *game);
void game_pause(GAME *game);
void game_over(GAME *game);
void game_pause(GAME *game);
void destroy_game(GAME *game);

// for unit test
PANEL _init_panel();
BLOCK _init_block(char type, int turn_idx); //type in "TOILJSZ"
BLOCK _rand_block();

void _panel_be_filled(GAME *game);
void _begin_next_frame(GAME *game);
void _check_eliminate(GAME *game);


#endif /*TETRIS_H_INCLUEDE*/
