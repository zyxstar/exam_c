#include "game.h"

typedef void(*GAME_ACTION)(GAME*);

typedef struct {
    char op;
    GAME* game;
    GAME_ACTION action;
} PRESS_HANDLER;


GAME_UI* ui_init();
void ui_destroy(GAME_UI *ui);

//cd order: `turn left right down pause`
void bind_press_handlers(GAME *game, char *cd, PRESS_HANDLER *handlers, int *size);

void key_press_loop(PRESS_HANDLER *handlers, int size);

