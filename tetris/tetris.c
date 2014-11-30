#include "stdlib.h"
#include "string.h"
#include "tetris.h"

PANEL _init_panel(){
    PANEL panel = malloc(ROWS * COLS * sizeof(int));
    assert(panel != NULL);
    int row, col;
    for(row = 0; row < ROWS; row++){
        for(col = 0; col < COLS; col++){
            panel[row][col] = EMPTY;
        }
    }
    return panel;
}

BLOCK _rand_block(){
    srand(time(NULL));
    char *types = "TOILJSZ";
    char type = types[rand()%strlen(types)];
    int turn_idx = rand()%4;
    return _init_block(type, turn_idx);
}

GAME* init_game(void(*draw_view)(GAME*)){
    GAME *game = malloc(sizeof(GAME));
    game->score = 0;
    game->panel = _init_panel();
    game->draw_view = draw_view;
    game->cur_block = _rand_block();
    game->next_block = _rand_block();
    return game;
}

//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
static int _get_type_idx(char type){
    char *types = "TOILJSZ";
    int i = 0;
    while(types[i]!='\0' && types[i] != type) i++;
    if(types[i] == type) return i;
    return -1;
}

void _config_base_pos_sets_of_T(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{2,1},{1,2}};
    POS_SET p1 = {{1,0},{1,1},{1,2},{0,1}};
    POS_SET p2 = {{2,1},{1,1},{0,1},{1,0}};
    POS_SET p3 = {{1,2},{1,1},{1,0},{2,1}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

void _config_base_pos_sets_of_O(POS_SET* sets){
    POS_SET p0 = {{0,0},{1,0},{0,1},{1,1}};
    sets[0] = sets[1] = sets[2] = sets[3] = p0;
}

void _config_base_pos_sets_of_I(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{2,1},{3,1}};
    POS_SET p1 = {{1,0},{1,1},{1,2},{1,3}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
}

void _config_base_pos_sets_of_L(POS_SET* sets){
    POS_SET p0 = {{1,0},{1,1},{1,2},{2,2}};
    POS_SET p1 = {{3,1},{2,1},{1,1},{1,2}};
    POS_SET p2 = {{2,3},{2,2},{2,1},{1,1}};
    POS_SET p3 = {{0,2},{1,2},{2,2},{2,1}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

void _config_base_pos_sets_of_J(POS_SET* sets){
    POS_SET p0 = {{2,0},{2,1},{2,2},{1,2}};
    POS_SET p1 = {{3,2},{2,2},{1,2},{1,1}};
    POS_SET p2 = {{1,3},{1,2},{1,1},{2,1}};
    POS_SET p3 = {{0,1},{1,1},{2,1},{2,2}};
    sets[0] = p0;
    sets[1] = p1;
    sets[2] = p2;
    sets[3] = p3;
}

void _config_base_pos_sets_of_S(POS_SET* sets){
    POS_SET p0 = {{0,1},{1,1},{1,0},{2,0}};
    POS_SET p1 = {{0,0},{0,1},{1,1},{1,2}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
}

void _config_base_pos_sets_of_Z(POS_SET* sets){
    POS_SET p0 = {{0,0},{1,1},{1,0},{2,1}};
    POS_SET p1 = {{1,0},{0,1},{1,1},{0,2}};
    sets[0] = sets[2] = p0;
    sets[1] = sets[3] = p1;
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
    config_set_fn[_get_type_idx(type)](b.base_pos_sets);
    b.pos_set = b.base_pos_sets[turn_idx];

    return b;
}

//////////////////////////////////////////////////////////////////////////
static BOOL _check_hit(const PANEL panel, BLOCK *b){
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
    if(!_check_hit((const PANEL)game->panel, b)){
        *b = backup_b;
        return FALSE;
    }
    game->draw_view(game);
    return TRUE;
}


BOOL move_left(GAME *game){
    POS left = {-1, 0};
    return _move(game, left);
}

BOOL move_right(GAME *game){
    POS right = {1, 0};
    return _move(game, right);
}


static void _panel_be_filled(GAME *game){
    POS *pos_set = (POS*)(&(game->cur_block.pos_set));
    int i;
    for(i = 0; i < 4; i++)
        game->panel[pos_set[i].y][pos_set[i].x] = FILLED;
    game->draw_view(game);
}

static int _check_eliminate(GAME *game){
    printf("eliminate\n");
    //add sroce
    game->draw_view(game);
    
}

BOOL _check_game_over(){}

void _begin_next(){}

BOOL move_down(GAME *game){
    POS down = {0, 1};
    //lock
    BOOL ret = _move(game, down);
    if(!ret){ //when down finished
        _panel_be_filled(game);
        _check_eliminate(game);
        if(!_check_game_over())
            _begin_next();
    }
    //unlock
    return ret;
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
    if(!_check_hit((const PANEL)panel, b)){
        *b = backup_b;
        return FALSE;
    }
    game->draw_view(game);
    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
void _print_panel(const PANEL panel){
    int row, col;
    printf("PANEL: \n");
    for(row = 0; row < ROWS; row++){
        printf("     ");
        for(col = 0; col < COLS; col++){
            printf("%c", panel[row][col] == FILLED ? '#' : '_');
        }
        printf(" : %2d\n", row);
    }
}


void _print_block(const BLOCK *b){
    printf("%c:%d", b->type, b->turn_idx);
    printf("[{%d,%d},{%d,%d},{%d,%d},{%d,%d}]\n",
            b->pos_set.pos0.x, b->pos_set.pos0.y,
            b->pos_set.pos1.x, b->pos_set.pos1.y,
            b->pos_set.pos2.x, b->pos_set.pos2.y,
            b->pos_set.pos3.x, b->pos_set.pos3.y);

    int row, col;
    for(row = 0; row < ROWS; row++){
        printf("%2d : ", row);
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


// int (*pnl)[COLS] = (int(*)[COLS])panel;
