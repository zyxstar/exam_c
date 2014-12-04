#include "utils.h"
#include "tetris.h"

#define FRM_TOP 2
#define FRM_WID 22
#define FRM_EX_WID 12
#define FRM_HEI 22

void clear_tty();
void reset_tty();

void draw_frame(int top, int left, char turn_cd, char left_cd, char right_cd, char down_cd);
void draw_level(int frame_top, int frame_left, int level);
void draw_score(int frame_top, int frame_left, int score);
void draw_next_block(int frame_top, int frame_left, BLOCK *block);
void draw_panel_block(int frame_top, int frame_left, BLOCK *block);
void erase_panel_block(int frame_top, int frame_left, BLOCK *block);
void draw_panel(int frame_top, int frame_left, PANEL panel);
void draw_over(int frame_top, int frame_left);
