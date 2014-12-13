#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

#define BUF_LEN (20)

void clear_tty(){
    printf(VT_CLEAR_SCREEN);
    printf(VT_HIED_CUR);
    echo_off();
    set_keypress();
}

void reset_tty(){
    reset_keypress();
    echo_on();
    printf(VT_SHOW_CUR);
    printf(VT_RESET VT_SET_CUR VT_RESET, FRM_TOP + FRM_HEI + 2, 0);
}

static void _draw_text(int x, int y, char *str, char *color, char *bg_color){
    printf(VT_RESET VT_SET_CUR "%s%s%s" VT_RESET, y, x, color, bg_color, str);
    printf(VT_SET_CUR, 0, 0);
    fflush(NULL);
}

static void _draw_rect(int top, int left, int width, int heigth, char *bg_color){
    int x, y;
    // for(x = 0; x < width - 2; x++)
    //     for(y = 0; y < heigth - 1; y++)
    //         _draw_text(left + x + 2, top + y + 2, " ", VT_GRAY, VT_BG_WHITE);

    for(x = 0; x < width; x++){
        _draw_text(left + x + 2, top + 1, " ", VT_GRAY, bg_color);
        _draw_text(left + x + 2, top + heigth, " ", VT_GRAY, bg_color);
    }
    for(y = 0; y < heigth; y++){
        _draw_text(left, top + y + 1, "  ", VT_GRAY, bg_color);
        _draw_text(left + width, top + y + 1, "  ", VT_GRAY, bg_color);
    }
}

static void _draw_operator(int frame_top, int frame_left, int top, char *operator, char cd){
    char str[BUF_LEN];
    snprintf(str, BUF_LEN, "%-5s: " VT_RED "%c", operator, cd);
    _draw_text(frame_left + FRM_WID + 3, frame_top + top, str, VT_DEEP VT_YELLOW, VT_BG_NONE);
}


void draw_frame(int top, int left, char turn_cd, char left_cd, char right_cd, char down_cd, char pause_cd){
    _draw_rect(top, left, FRM_WID, FRM_HEI, VT_BG_BLUE);
    _draw_rect(top, left + FRM_WID, FRM_EX_WID, FRM_HEI, VT_BG_BLUE);
    _draw_operator(top, left, 14, "turn", turn_cd);
    _draw_operator(top, left, 15, "left", left_cd);
    _draw_operator(top, left, 16, "rignt", right_cd);
    _draw_operator(top, left, 17, "down", down_cd);
    _draw_operator(top, left, 18, "pause", pause_cd);
    _draw_operator(top, left, 19, "quit", 'q');
}

void draw_level(int frame_top, int frame_left, int level){
    char str[BUF_LEN];
    snprintf(str, BUF_LEN, "LEVEL %d", level);
    _draw_text(frame_left + FRM_WID + 3, frame_top + 3, str, VT_DEEP VT_YELLOW, VT_BG_NONE);
}

void draw_score(int frame_top, int frame_left, int score){
    char str[BUF_LEN];
    snprintf(str, BUF_LEN, VT_DEEP VT_RED "%d", score);
    _draw_text(frame_left + FRM_WID + 4, frame_top + 5, str, VT_DEEP VT_YELLOW, VT_BG_NONE);
}

static void _draw_block(int top, int left, BLOCK *block, char *text, char *bg_color){
    POS *pos_set = (POS*)(&(block->pos_set));
    int i;
    for(i = 0; i < 4; i++){
        _draw_text(left + pos_set[i].x * 2, top + pos_set[i].y, text, VT_GRAY, bg_color);
    }
}

void draw_next_block(int frame_top, int frame_left, BLOCK *block){
    int top=8;
    while(top < 12)
        _draw_text(frame_left + FRM_WID + 2, frame_top + top++, "          ", VT_GRAY, VT_BG_NONE);
    _draw_block(frame_top + 8, frame_left + FRM_WID - 3, block, "[]", VT_BG_CYAN);
}

void draw_panel_block(int frame_top, int frame_left, BLOCK *block){
    _draw_block(frame_top + 2, frame_left + 2, block, "[]", VT_BG_CYAN);
}

void erase_panel_block(int frame_top, int frame_left, BLOCK *block){
    _draw_block(frame_top + 2, frame_left + 2, block, "  ", VT_BG_NONE);
}


void draw_panel(int frame_top, int frame_left, PANEL panel){
    DEBUG_WRITE(("draw_panel begin\n"));
    int row, col;
    int base_x = frame_left + 2;
    int base_y = frame_top + 2;
    for(row = 0; row < ROWS; row++)
        for(col = 0; col < COLS; col++)
            if(panel[row][col] == FILLED)
                _draw_text(base_x + col * 2, base_y + row, "[]", VT_GRAY, VT_BG_PURPLE);
            else
                _draw_text(base_x + col * 2, base_y + row, "  ", VT_GRAY, VT_BG_NONE);
    DEBUG_WRITE(("draw_panel end\n"));
}

static void _draw_highlight(int frame_top, int frame_left, int *lines, int lines_size, char *bg_color){
    int i, col;
    int base_x = frame_left + 2;
    int base_y = frame_top + 2;
    for(i = 0; i < lines_size; i++)
        for(col = 0; col < COLS; col++)
            _draw_text(base_x + col * 2, base_y + lines[i], "[]", VT_GRAY, bg_color);
}

void draw_highlight(int frame_top, int frame_left, int *lines, int lines_size){
    _draw_highlight(frame_top, frame_left, lines, lines_size, VT_BG_BLUE);
}

void erase_highlight(int frame_top, int frame_left, int *lines, int lines_size){
    _draw_highlight(frame_top, frame_left, lines, lines_size, VT_BG_NONE);
}


static void _draw_tip(int frame_top, int frame_left, char *text){
    char str[BUF_LEN];
    snprintf(str, BUF_LEN, "%-11s", text);
    _draw_text(frame_left + 7, frame_top, str, VT_RED, VT_BG_NONE);
}

void draw_over(int frame_top, int frame_left){
    _draw_tip(frame_top, frame_left, "Game Over!");
}

void draw_pause(int frame_top, int frame_left){
    _draw_tip(frame_top, frame_left, "Pause!");
}

void draw_running(int frame_top, int frame_left){
    _draw_tip(frame_top, frame_left, "Running...");
}

void voice(){
    printf("%c", 7);
    fflush(NULL);
}




