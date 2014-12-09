#ifndef GAME_H_INCLUEDE
#define GAME_H_INCLUEDE

#include <pthread.h>
#include "utils.h"

#define ROWS (20)
#define COLS (10)

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

typedef struct GAME_TAG GAME;

typedef struct GAME_UI_TAG{
    int frame_left;
    SIMPER_TIMER timer;
    int tick_count;
    GAME *game;

    void(*draw_level)(struct GAME_UI_TAG*);
    void(*draw_score)(struct GAME_UI_TAG*);
    void(*draw_next)(struct GAME_UI_TAG*);

    void(*draw_block)(struct GAME_UI_TAG*);
    void(*draw_change)(BLOCK *last, struct GAME_UI_TAG*);
    void(*draw_eliminate)(struct GAME_UI_TAG*, int *lines, int lines_size);
    void(*draw_panel)(struct GAME_UI_TAG*);
    void(*draw_pause)(struct GAME_UI_TAG*);
    void(*draw_running)(struct GAME_UI_TAG*);
    void(*draw_game_over)(struct GAME_UI_TAG*);
} GAME_UI;


struct GAME_TAG{
    int score;
    int level;
    PANEL panel;
    BLOCK cur_block;
    BLOCK next_block;

    BOOL is_over;
    BOOL is_pause;

    SIMPER_TIMER timer;
    GAME_UI *ui;

    pthread_mutex_t mutex;
};


// interface
GAME* game_init(GAME_UI *ui);
void game_begin(GAME *game);
void game_pause(GAME *game);
void game_over(GAME *game);
void game_destroy(GAME *game);

BOOL game_move_left(GAME *game);
BOOL game_move_right(GAME *game);
BOOL game_move_down(GAME *game);
BOOL game_turn(GAME *game); //means turn left



// for unit test
PANEL _init_panel();
BLOCK _init_block(char type, int turn_idx); //type in "TOILJSZ"
BLOCK _rand_block();

void _panel_be_filled(GAME *game);
void _begin_next(GAME *game);
void _check_eliminate(GAME *game);


#endif /*GAME_H_INCLUEDE*/
