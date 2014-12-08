#include "utils.h"
#include "game.h"

#define FRM_TOP (1)
#define FRM_WID (22)
#define FRM_EX_WID (12)
#define FRM_HEI (22)

void clear_tty();
void reset_tty();

void draw_frame(int top, int left, char turn_cd, char left_cd, char right_cd, char down_cd, char pause_cd);
void draw_level(int frame_top, int frame_left, int level);
void draw_score(int frame_top, int frame_left, int score);
void draw_next_block(int frame_top, int frame_left, BLOCK *block);
void draw_panel_block(int frame_top, int frame_left, BLOCK *block);
void erase_panel_block(int frame_top, int frame_left, BLOCK *block);
void draw_panel(int frame_top, int frame_left, PANEL panel);
void draw_highlight(int frame_top, int frame_left, int *lines, int lines_size);
void draw_over(int frame_top, int frame_left);
void draw_pause(int frame_top, int frame_left);
void draw_running(int frame_top, int frame_left);

