#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "game.h"

PANEL _init_panel(){
    DEBUG_WRITE(("_init_panel begin\n"));
    PANEL panel = malloc(ROWS * COLS * sizeof(int));
    // int (*pnl)[COLS] = (int(*)[COLS])panel;
    assert(panel != NULL);
    int row, col;
    for(row = 0; row < ROWS; row++)
        for(col = 0; col < COLS; col++)
            panel[row][col] = EMPTY;

    DEBUG_WRITE(("_init_panel end\n"));
    return panel;
}

BLOCK _rand_block(){
    char *types = "TOILJSZ";
    char type = types[rand()%strlen(types)];
    int turn_idx = rand()%4;
    DEBUG_WRITE(("_rand_block: [type]%c, [turn_idx]%d\n", type, turn_idx));
    return _init_block(type, turn_idx);
}

void _timer_hander_fn(void *env){
    game_move_down((GAME*)env);
}

GAME* game_init(GAME_UI *ui){
    DEBUG_WRITE(("game_init begin\n"));
    GAME *game = malloc(sizeof(GAME));
    game->ui = ui;
    game->score = 0;
    game->level = 1;
    game->is_over = FALSE;
    game->is_pause = FALSE;
    game->panel = _init_panel();
    game->cur_block = _rand_block();
    game->next_block = _rand_block();

    timer_new(&game->timer, 1000, _timer_hander_fn, game);
    pthread_mutex_init(&game->mutex, NULL);
    DEBUG_WRITE(("game_init end\n"));
    return game;
}

void game_begin(GAME *game){
    DEBUG_WRITE(("game_begin begin\n"));
    game->ui->draw_level(game->ui);
    game->ui->draw_score(game->ui);
    game->ui->draw_next(game->ui);
    game->ui->draw_panel(game->ui);
    game->ui->draw_block(game->ui);
    game->ui->draw_running(game->ui);

    timer_start(&game->timer);
    DEBUG_WRITE(("game_begin end\n"));
}

void game_pause(GAME *game){
    if(game->is_over) return;
    if(!game->is_pause){
        timer_stop(&game->timer);
        game->ui->draw_pause(game->ui);
        game->is_pause = TRUE;
    }
    else{
        timer_start(&game->timer);
        game->ui->draw_running(game->ui);
        game->is_pause = FALSE;
    }
}


//////////////////////////////////////////////////////////////////////////
static int _get_type_idx(char type){
    char *types = "TOILJSZ";
    int i = 0;
    while(types[i]!='\0' && types[i] != type) i++;
    if(types[i] == type) return i;
    assert(FALSE);
}

static void _config_base_pos_sets_of_T(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{2,1},{1,2}};
    POS_SET p1 = {{1,0},{1,1},{1,2},{0,1}};
    POS_SET p2 = {{2,1},{1,1},{0,1},{1,0}};
    POS_SET p3 = {{1,2},{1,1},{1,0},{2,1}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

static void _config_base_pos_sets_of_O(POS_SET* sets){
    POS_SET p0 = {{1,0},{2,0},{1,1},{2,1}};
    sets[0] = sets[1] = sets[2] = sets[3] = p0;
}

static void _config_base_pos_sets_of_I(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{2,1},{3,1}};
    POS_SET p1 = {{1,0},{1,1},{1,2},{1,3}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
}

static void _config_base_pos_sets_of_L(POS_SET* sets){
    POS_SET p0 = {{1,0},{1,1},{1,2},{2,2}};
    POS_SET p1 = {{3,1},{2,1},{1,1},{1,2}};
    POS_SET p2 = {{2,3},{2,2},{2,1},{1,1}};
    POS_SET p3 = {{0,2},{1,2},{2,2},{2,1}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

static void _config_base_pos_sets_of_J(POS_SET* sets){
    POS_SET p0 = {{2,0},{2,1},{2,2},{1,2}};
    POS_SET p1 = {{3,2},{2,2},{1,2},{1,1}};
    POS_SET p2 = {{1,3},{1,2},{1,1},{2,1}};
    POS_SET p3 = {{0,1},{1,1},{2,1},{2,2}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

static void _config_base_pos_sets_of_S(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{1,0},{2,0}};
    POS_SET p1 = {{0,0},{0,1},{1,1},{1,2}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
}

static void _config_base_pos_sets_of_Z(POS_SET* sets){
    POS_SET p0 = {{0,0},{1,1},{1,0},{2,1}};
    POS_SET p1 = {{1,0},{0,1},{1,1},{0,2}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
}

static POS_SET _move_center(POS_SET pos_set){
    int offset = COLS / 2 - 2;
    POS *set = (POS*)(&pos_set);
    int i;
    for(i = 0; i < 4; i++)
        set[i].x += offset;
    return pos_set;
}

BLOCK _init_block(char type, int turn_idx){
    void(*config_set_fn[])(POS_SET*) = {
        _config_base_pos_sets_of_T,
        _config_base_pos_sets_of_O,
        _config_base_pos_sets_of_I,
        _config_base_pos_sets_of_L,
        _config_base_pos_sets_of_J,
        _config_base_pos_sets_of_S,
        _config_base_pos_sets_of_Z
    };

    BLOCK b;
    b.type = type;
    b.turn_idx = turn_idx;
    b.down_count = 0;
    config_set_fn[_get_type_idx(type)](b.base_pos_sets);
    b.pos_set = _move_center(b.base_pos_sets[turn_idx]);
    return b;
}

//////////////////////////////////////////////////////////////////////////
static BOOL _check_hit(PANEL panel, BLOCK *b){
    POS *pos_set = (POS*)(&b->pos_set);
    int i, pos_y, pos_x;
    for(i = 0; i < 4; i++){
        pos_x = pos_set[i].x;
        pos_y = pos_set[i].y;
        // out of panel
        if(pos_x >= COLS || pos_x < 0 || pos_y >= ROWS) return FALSE;
        // this postion is not empty
        if(panel[pos_y][pos_x] != EMPTY) return FALSE;
    }
    return TRUE;
}

static BOOL _move(GAME *game, POS direction){
    BLOCK *b = &game->cur_block;
    BLOCK backup_b = *b;
    POS *pos_set = (POS*)(&b->pos_set);
    int i;
    for(i = 0; i < 4; i++){
        pos_set[i].x += direction.x;
        pos_set[i].y += direction.y;
    }
    if(!_check_hit(game->panel, b)){
        *b = backup_b;
        return FALSE;
    }
    game->ui->draw_change(&backup_b, game->ui);
    return TRUE;
}


BOOL game_move_left(GAME *game){
    if(game->is_over || game->is_pause) return FALSE;
    DEBUG_WRITE(("game_move_left begin\n"));
    POS left = {-1, 0};
    BOOL is_moved = _move(game, left);
    DEBUG_WRITE(("game_move_left end: [is_moved]%s\n", human_bool(is_moved)));
    return is_moved;
}

BOOL game_move_right(GAME *game){
    if(game->is_over || game->is_pause) return FALSE;
    DEBUG_WRITE(("game_move_right begin\n"));
    POS right = {1, 0};
    BOOL is_moved = _move(game, right);
    DEBUG_WRITE(("game_move_right end: [is_moved]%s\n", human_bool(is_moved)));
    return is_moved;
}

//////////////////////////////////////////////////////////////////////////


void _panel_be_filled(GAME *game){
    DEBUG_WRITE(("_panel_be_filled begin\n"));
    POS *pos_set = (POS*)(&game->cur_block.pos_set);
    int i;
    for(i = 0; i < 4; i++)
        game->panel[pos_set[i].y][pos_set[i].x] = FILLED;
    game->ui->draw_panel(game->ui);
    DEBUG_WRITE(("_panel_be_filled end\n"));
}

void _begin_next(GAME *game){
    DEBUG_WRITE(("_begin_next begin\n"));
    game->cur_block = game->next_block;
    game->next_block = _rand_block();
    game->ui->draw_block(game->ui);
    game->ui->draw_next(game->ui);
    DEBUG_WRITE(("_begin_next end: [next]%c%d\n",
        game->next_block.type, game->next_block.turn_idx));
}

static BOOL _all_cols_be_filled(PANEL panel, int row){
    int col;
    for(col = 0; col < COLS; col++)
        if(panel[row][col] == EMPTY) return FALSE;
    return TRUE;
}

static void _eliminate(PANEL panel, int row){
    int col, r;
    for(r = row; r > 0; r--){
        for(col = 0; col < COLS; col++){
            panel[r][col] = panel[r-1][col];
        }
    }
    for(col = 0; col < COLS; col++)
        panel[0][col] = EMPTY;
}

static int _calc_score(int lines){
    assert(lines >= 0 && lines <= 4);
    int rules[] = {0, 100, 200, 400, 800};
    return rules[lines];
}

static void _speed_up(GAME *game){
    int interval = 1000 - game->level * 200;
    interval = interval > 0 ? interval : 10;
    timer_set_interval(&game->timer, interval);
}

static void _check_level_up(GAME *game){
    int level = game->score / 1000 + 1;
    if(game->level != level){
        game->level = level;
        _speed_up(game);
        game->ui->draw_level(game->ui);
    }
}

void _check_eliminate(GAME *game){
    DEBUG_WRITE(("_check_eliminate begin\n"));
    int row, lines = 0;
    for(row = 0; row < ROWS; row++){
        if(_all_cols_be_filled(game->panel, row)){
            lines++;
            _eliminate(game->panel, row);
        }
    }
    if(lines > 0){
        game->score += _calc_score(lines);
        _check_level_up(game);
        game->ui->draw_score(game->ui);
        game->ui->draw_panel(game->ui);
    }
    DEBUG_WRITE(("_check_eliminate end: [lines]\n", lines));
}


static BOOL _check_game_over(GAME *game){
    DEBUG_WRITE(("_check_game_over: [down_count]\n", game->cur_block.down_count));
    return game->cur_block.down_count == 0;
}

void game_over(GAME *game){
    DEBUG_WRITE(("game_over begin\n"));
    timer_stop(&game->timer);
    pthread_mutex_destroy(&game->mutex);

    game->is_over = TRUE;
    game->ui->draw_game_over(game->ui);

    DEBUG_WRITE(("game_over end\n"));
}

void game_destroy(GAME *game){
    DEBUG_WRITE(("game_destroy begin\n"));

    timer_destroy(&game->timer);
    free(game->panel);
    free(game);
    DEBUG_WRITE(("game_destroy end\n"));
}

BOOL game_move_down(GAME *game){
    if(game->is_over || game->is_pause) return FALSE;
    DEBUG_WRITE(("game_move_down begin\n"));

    pthread_mutex_lock(&game->mutex);
    POS down = {0, 1};
    BOOL is_moved = _move(game, down);
    
    if(!is_moved){ //when down finished
        if(_check_game_over(game))
            game_over(game);

        _panel_be_filled(game);
        _check_eliminate(game);
        _begin_next(game);
    }
    else{
        game->cur_block.down_count++;
    }
    pthread_mutex_unlock(&game->mutex);
    DEBUG_WRITE(("game_move_down end: [is_moved]%s\n", human_bool(is_moved)));
    return is_moved;
}


//////////////////////////////////////////////////////////////////////////
POS_SET _pos_set_diff(POS_SET set1, POS_SET set2, int sign){//sign is 1 or -1
    POS *pos_set1 = (POS*)(&set1);
    POS *pos_set2 = (POS*)(&set2);
    POS ret[4];
    int i;
    for(i = 0; i < 4; i++){
        ret[i].x = pos_set1[i].x + (pos_set2[i].x) * sign;
        ret[i].y = pos_set1[i].y + (pos_set2[i].y) * sign;
    }
    return *((POS_SET*)ret);
}

static void _turn_block(BLOCK *b){
    POS_SET base_pos_set = b->base_pos_sets[b->turn_idx];
    POS_SET offset = _pos_set_diff(b->pos_set, base_pos_set, -1);
    b->turn_idx = (b->turn_idx + 1) % 4;
    b->pos_set = _pos_set_diff(b->base_pos_sets[b->turn_idx], offset, 1);
}

BOOL game_turn(GAME *game){
    if(game->is_over || game->is_pause) return FALSE;
    DEBUG_WRITE(("game_turn begin\n"));
    BLOCK *b = &game->cur_block;
    BLOCK backup_b = *b;
    BOOL is_turned = TRUE;
    _turn_block(b);
    if(!_check_hit(game->panel, b)){
        *b = backup_b;
        is_turned = FALSE;
    }
    game->ui->draw_change(&backup_b, game->ui);
    DEBUG_WRITE(("game_turn end\n"));
    return is_turned;
}




