#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tetris.h"

PANEL _init_panel(){
    DEBUG_WRITE(("_init_panel begin\n"));
    PANEL panel = malloc(ROWS * COLS * sizeof(int));
    assert(panel != NULL);
    int row, col;
    for(row = 0; row < ROWS; row++){
        for(col = 0; col < COLS; col++){
            panel[row][col] = EMPTY;
        }
    }
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

void _wrap_draw_view(GAME *game){
    DEBUG_WRITE(("_wrap_draw_view begin\n"));
    //lock
    game->_origin_draw_view(game);
    //unlock
    DEBUG_WRITE(("_wrap_draw_view end\n"));
}

GAME* init_game(void(*draw_view)(GAME*)){
    DEBUG_WRITE(("init_game begin\n"));
    GAME *game = malloc(sizeof(GAME));
    game->score = 0;
    game->panel = _init_panel();
    game->_origin_draw_view = draw_view;
    game->draw_view = _wrap_draw_view;
    srand(time(NULL));
    game->cur_block = _rand_block();
    game->next_block = _rand_block();
    DEBUG_WRITE(("init_game end\n"));
    return game;
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
    POS *pos_set = (POS*)(&(b->pos_set));
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
    BLOCK *b = &(game->cur_block);
    BLOCK backup_b = *b;
    POS *pos_set = (POS*)(&(b->pos_set));
    int i;
    for(i = 0; i < 4; i++){
        pos_set[i].x += direction.x;
        pos_set[i].y += direction.y;
    }
    if(!_check_hit(game->panel, b)){
        *b = backup_b;
        return FALSE;
    }
    game->draw_view(game);
    return TRUE;
}


BOOL move_left(GAME *game){
    DEBUG_WRITE(("move_left begin\n"));
    POS left = {-1, 0};
    BOOL is_moved = _move(game, left);
    DEBUG_WRITE(("move_left end: [is_moved]%s\n", human_bool(is_moved)));
    return is_moved;
}

BOOL move_right(GAME *game){
    DEBUG_WRITE(("move_right begin\n"));
    POS right = {1, 0};
    BOOL is_moved = _move(game, right);
    DEBUG_WRITE(("move_right end: [is_moved]%s\n", human_bool(is_moved)));
    return is_moved;
}

void _panel_be_filled(GAME *game){
    DEBUG_WRITE(("_panel_be_filled begin\n"));
    POS *pos_set = (POS*)(&(game->cur_block.pos_set));
    int i;
    for(i = 0; i < 4; i++)
        game->panel[pos_set[i].y][pos_set[i].x] = FILLED;
    DEBUG_WRITE(("_panel_be_filled end\n"));
}

void _begin_next_frame(GAME *game){
    DEBUG_WRITE(("_begin_next_frame begin\n"));
    game->cur_block = game->next_block;
    game->next_block = _rand_block();
    game->draw_view(game);
    DEBUG_WRITE(("_begin_next_frame end: [next]%c%d\n",
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

int _check_eliminate(GAME *game){
    DEBUG_WRITE(("_check_eliminate begin\n"));
    int row, lines = 0;
    for(row = 0; row < ROWS; row++){
        if(_all_cols_be_filled(game->panel, row)){
            lines++;
            _eliminate(game->panel, row);
        }
    }
    if(lines > 0) game->draw_view(game);
    DEBUG_WRITE(("_check_eliminate end: [lines]\n", lines));
    return lines;
}

static int _calc_score(int lines){
    assert(lines >= 0 && lines <= 4);
    int rules[] = {0, 100, 200, 400, 800};
    return rules[lines];
}

static BOOL _check_game_over(GAME *game){
    DEBUG_WRITE(("_check_game_over: [down_count]\n", game->cur_block.down_count));
    return game->cur_block.down_count == 0;
}

void game_over(GAME *game){
    DEBUG_WRITE(("game_over begin\n"));
    game->draw_game_over(game);
    free(game->panel);
    free(game);
    DEBUG_WRITE(("game_over end\n"));
}

BOOL move_down(GAME *game){
    DEBUG_WRITE(("move_down begin\n"));
    POS down = {0, 1};
    //lock
    BOOL is_moved = _move(game, down);
    if(!is_moved){ //when down finished
        if(_check_game_over(game))
            game_over(game);

        _panel_be_filled(game);
        _begin_next_frame(game);
        int lines = _check_eliminate(game);
        game->score += _calc_score(lines);
    }
    else game->cur_block.down_count++;

    //unlock
    DEBUG_WRITE(("move_down end: [is_moved]%s\n", human_bool(is_moved)));
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

static void _trun_block(BLOCK *b){
    POS_SET base_pos_set = b->base_pos_sets[b->turn_idx];
    POS_SET offset = _pos_set_diff(b->pos_set, base_pos_set, -1);
    b->turn_idx = (b->turn_idx + 1) % 4;
    b->pos_set = _pos_set_diff(b->base_pos_sets[b->turn_idx], offset, 1);
}

BOOL turn(GAME *game){
    BLOCK *b = &(game->cur_block);
    BLOCK backup_b = *b;
    _trun_block(b);
    if(!_check_hit(game->panel, b)){
        *b = backup_b;
        return FALSE;
    }
    game->draw_view(game);
    return TRUE;
}


















//////////////////////////////////////////////////////////////////////////
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
    printf("\nGAME: [sroce]%d, [draw_view]%p, [next]%c%d\n", game->score, game->draw_view, game->next_block.type, game->next_block.turn_idx);
    _print_block(&game->cur_block);
    _print_panel(game->panel);
}


// int (*pnl)[COLS] = (int(*)[COLS])panel;
