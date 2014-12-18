#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include "utils.h"
#include "ctrl.h"


static void _draw_level_fn(GAME_UI *ui){
    draw_level(FRM_TOP, ui->frame_left, ui->game->level);
}

static void _draw_score_fn(GAME_UI *ui){
    draw_score(FRM_TOP, ui->frame_left, ui->game->score);
}

static void _draw_next_fn(GAME_UI *ui){
    draw_next_block(FRM_TOP, ui->frame_left, &ui->game->next_block);
}

static void _draw_change_fn(BLOCK *last, GAME_UI *ui){
    erase_panel_block(FRM_TOP, ui->frame_left, last);
    draw_panel_block(FRM_TOP, ui->frame_left, &ui->game->cur_block);
}

static void _draw_panel_fn(GAME_UI *ui){
    draw_panel(FRM_TOP, ui->frame_left, ui->game->panel);
}

static void _draw_block_fn(GAME_UI *ui){
    draw_panel_block(FRM_TOP, ui->frame_left, &ui->game->cur_block);
}

static void _draw_pause_fn(GAME_UI *ui){
    draw_pause(FRM_TOP, ui->frame_left);
}

static void _draw_running_fn(GAME_UI *ui){
    draw_running(FRM_TOP, ui->frame_left);
}

static void _draw_game_over_fn(GAME_UI *ui){
    draw_over(FRM_TOP, ui->frame_left);
}

static void _ui_timer_call(void *env){// implement animation
    GAME_UI *ui = (GAME_UI*)((void**)env)[0];
    if(ui->timer.interval == 0) return;

    int *data = (int*)((void **)env)[1];
    int lines_size = data[0];
    int *lines = &data[1];

    switch(ui->tick_count){
        case 0:
            erase_highlight(FRM_TOP, ui->frame_left, lines, lines_size);
            ui->tick_count++;
            break;
        // case 1:
        //     draw_highlight(FRM_TOP, ui->frame_left, lines, lines_size);
        //     ui->tick_count++;
        //     break;
        case 1:
            timer_stop(&ui->timer);
            draw_panel(FRM_TOP, ui->frame_left, ui->game->panel);
            draw_panel_block(FRM_TOP, ui->frame_left, &ui->game->cur_block);
            ui->tick_count = 0;
            free(data);
            free(env);
            break;
    }
}

static void _draw_eliminate_fn(GAME_UI *ui, int *lines, int lines_size){
    draw_highlight(FRM_TOP, ui->frame_left, lines, lines_size);
    int *data = malloc(sizeof(int*) * lines_size + 1);
    data[0] = lines_size;
    int i;
    for(i = 1; i < lines_size + 1; i++)
        data[i] = lines[i-1];

    void **env = malloc(sizeof(void*) * 2);
    env[0] = ui;
    env[1] = data;

    ui->timer.env = env;
    timer_set_interval(&ui->timer, ui->game->timer.const_interval / 20);
    timer_start(&ui->timer);
}

GAME_UI* ui_init(int frame_left, char **cd){
    GAME_UI *ui = malloc(sizeof(GAME_UI));
    ui->tick_count = 0;
    ui->game = NULL;
    timer_new(&ui->timer, 100, _ui_timer_call, NULL);
    ui->frame_left = frame_left;
    ui->draw_level = _draw_level_fn;
    ui->draw_score = _draw_score_fn;
    ui->draw_next = _draw_next_fn;
    ui->draw_block = _draw_block_fn;
    ui->draw_change = _draw_change_fn;
    ui->draw_panel = _draw_panel_fn;
    ui->draw_eliminate = _draw_eliminate_fn;
    ui->draw_pause = _draw_pause_fn;
    ui->draw_running = _draw_running_fn;
    ui->draw_game_over = _draw_game_over_fn;
    draw_frame(FRM_TOP, frame_left, cd[0], cd[1], cd[2], cd[3], cd[4]);
    return ui;
}


void ui_destroy(GAME_UI *ui){
    timer_destroy(&ui->timer);
    free(ui);
}


static void register_press_handler(char op, GAME* game, GAME_ACTION action, PRESS_HANDLER *handlers, int *size){
    PRESS_HANDLER h = {op, game, action};
    handlers[*size] = h;
    *size += 1;
}

void bind_press_handlers(GAME *game, char **cd, PRESS_HANDLER *handlers, int *size){
    register_press_handler(cd[0][0], game, (GAME_ACTION)game_turn, handlers, size);
    register_press_handler(cd[1][0], game, (GAME_ACTION)game_move_left, handlers, size);
    register_press_handler(cd[2][0], game, (GAME_ACTION)game_move_right, handlers, size);
    register_press_handler(cd[3][0], game, (GAME_ACTION)game_move_down, handlers, size);
    register_press_handler(cd[4][0], game, game_pause, handlers, size);
}

void key_press_loop(PRESS_HANDLER *handlers, int size){
    char ch;
    int i;
    while((ch = getchar()) != 'q'){
        for(i = 0; i < size; i++)
            if(handlers[i].op == ch){
                handlers[i].action(handlers[i].game);
            }
        fflush(NULL);
    }
}





