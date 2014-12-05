#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"

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
    char str[20];
    sprintf(str, "%-5s: " VT_RED "%c", operator, cd);
    _draw_text(frame_left + FRM_WID + 3, frame_top + top, str, VT_DEEP VT_YELLOW, VT_BG_NONE);
}


void draw_frame(int top, int left, char turn_cd, char left_cd, char right_cd, char down_cd){
    _draw_rect(top, left, FRM_WID, FRM_HEI, VT_BG_BLUE);
    _draw_rect(top, left + FRM_WID, FRM_EX_WID, FRM_HEI, VT_BG_BLUE);
    _draw_operator(top, left, 14, "turn", turn_cd);
    _draw_operator(top, left, 15, "left", left_cd);
    _draw_operator(top, left, 16, "rignt", right_cd);
    _draw_operator(top, left, 17, "down", down_cd);
    _draw_operator(top, left, 18, "pause", 'p');
    _draw_operator(top, left, 19, "quit", 'q');
}

void draw_level(int frame_top, int frame_left, int level){
    char str[20];
    sprintf(str, "LEVEL %d", level);
    _draw_text(frame_left + FRM_WID + 3, frame_top + 3, str, VT_DEEP VT_YELLOW, VT_BG_NONE);
}

void draw_score(int frame_top, int frame_left, int score){
    char str[20];
    sprintf(str, VT_DEEP VT_RED "%d", score);
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
    int row, col;
    int base_x = frame_left + 2;
    int base_y = frame_top + 2;
    for(row = 0; row < ROWS; row++)
        for(col = 0; col < COLS; col++)
            if(panel[row][col] == FILLED)
                _draw_text(base_x + col * 2, base_y + row, "[]", VT_GRAY, VT_BG_PURPLE);
            else
                _draw_text(base_x + col * 2, base_y + row, "  ", VT_GRAY, VT_BG_NONE);

}

static void _draw_tip(int frame_top, int frame_left, char *text){
    char str[12];
    sprintf(str, "%-11s", text);
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


// void _test(){
//     clear_tty();
//     PANEL panel = _init_panel();
//     panel[0][1]=FILLED;
//     panel[1][1]=FILLED;
//     panel[5][5]=FILLED;
//     panel[6][6]=FILLED;
//     panel[11][6]=FILLED;
//     panel[12][6]=FILLED;
//     panel[13][6]=FILLED;
//     panel[14][6]=FILLED;
//     panel[15][6]=FILLED;
//     panel[19][9]=FILLED;

//     draw_frame(FRM_TOP, 5, 'w','a','d','s');
//     draw_level(FRM_TOP, 5, 2);
//     draw_score(FRM_TOP, 5, 1200);
//     BLOCK b = _init_block('T', 0);
//     draw_next_block(FRM_TOP, 5, &b);
//     draw_panel_block(FRM_TOP, 5, &b);
//     draw_panel(FRM_TOP, 5, panel);


//     draw_frame(FRM_TOP, 45, 'i','j','l','k');
//     draw_level(FRM_TOP, 45, 3);
//     draw_score(FRM_TOP, 45, 800);
//     BLOCK b2 = _init_block('O', 1);
//     draw_next_block(FRM_TOP, 45, &b2);
//     draw_panel_block(FRM_TOP, 45, &b2);
//     draw_panel(FRM_TOP, 45, panel);

//     // while(1);

//     reset_tty();

// }


// int main(){_test();return 0;}


// gcc -I ../utils ../utils/utils.c game.c view.c -o view.out && ./view.out





