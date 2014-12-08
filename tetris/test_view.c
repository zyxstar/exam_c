#include "view.h"

void test_view(){
    clear_tty();
    PANEL panel = _init_panel();
    panel[0][1]=FILLED;
    panel[1][1]=FILLED;
    panel[5][5]=FILLED;
    panel[6][6]=FILLED;
    panel[11][6]=FILLED;
    panel[12][6]=FILLED;
    panel[13][6]=FILLED;
    panel[14][6]=FILLED;
    panel[15][6]=FILLED;
    panel[19][9]=FILLED;

    draw_frame(FRM_TOP, 5, 'w','a','d','s','p');
    draw_level(FRM_TOP, 5, 2);
    draw_score(FRM_TOP, 5, 1200);
    BLOCK b = _init_block('T', 0);
    draw_next_block(FRM_TOP, 5, &b);
    draw_panel_block(FRM_TOP, 5, &b);
    draw_panel(FRM_TOP, 5, panel);
    draw_pause(FRM_TOP, 5);


    draw_frame(FRM_TOP, 45, 'i','j','l','k','p');
    draw_level(FRM_TOP, 45, 3);
    draw_score(FRM_TOP, 45, 800);
    BLOCK b2 = _init_block('O', 1);
    draw_next_block(FRM_TOP, 45, &b2);
    draw_panel_block(FRM_TOP, 45, &b2);
    draw_panel(FRM_TOP, 45, panel);
    draw_running(FRM_TOP, 45);

    reset_tty();

}


int main(){
    test_view();
    return 0;
}


// gcc -I ../utils ../utils/utils.c game.c view.c test_view.c -o test_view.out && ./test_view.out
