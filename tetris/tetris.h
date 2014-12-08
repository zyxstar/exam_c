
#include "game.h"

typedef void(*GAME_ACTION)(GAME*);

typedef struct {
    char op;
    GAME* game;
    GAME_ACTION action;
} PRESS_HANDLER;

void key_press_loop(PRESS_HANDLER *handlers, int size);
GAME* game_facade(GAME_UI *ui, int frame_left,
                 char turn_cd, char left_cd, char right_cd, char down_cd, char pause_cd,
                 PRESS_HANDLER *handlers, int *size);
