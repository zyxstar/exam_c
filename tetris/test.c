#include "tetris.h"
#include "utils.h"


void each_type_do(void(*callback)(char type)){
    char *types = "TOILJSZ";
    int i = 0;
    while(types[i]!='\0'){
        callback(types[i]);
        i++;
    }
}

int GLOBAL_PANEL[ROWS][COLS] = {0};

////////////////////////////////////////
void test_init_panel(){
    PANEL panel = _init_panel();
    _print_panel((const PANEL)panel);
    free(panel);
}
////////////////////////////////////////
void test_print_block_callback(char type){
    BLOCK b;
    int i;
    for(i = 0; i < 4; i++) {
        b = init_block(type, i);
        _print_block(&b);
    }
}
void test_print_block(){
    each_type_do(test_print_block_callback);
}
////////////////////////////////////////
void _test_move(char type, char *direction_str, BOOL(*func)(GAME*) ,int times){
    BLOCK b = init_block(type,0);
    int i;
    BOOL ret;
    for(i = 1; i <= times; i++){
        ret = func((PANEL)GLOBAL_PANEL, &b);
        printf("%c: %s[%d]: %s\n",type, direction_str, i, human_bool(ret));
        _print_block(&b);
        _print_panel((PANEL)GLOBAL_PANEL);
        if(!ret) break;
    }
}

void test_move_left(char type){
    _test_move(type, "left", move_left, 10);
}
void test_move_right(char type){
    _test_move(type, "right", move_right, 10);
}
void test_move_down(char type){
    _test_move(type, "down", move_down, 20);
}

void test_move_with_filled(char type){
    GLOBAL_PANEL[6][1] = FILLED;
    _test_move(type, "down", move_down, 20);    
}


////////////////////////////////////////
void test_turn_block(char type){
    BLOCK b = init_block(type,0);
    PANEL panel = (PANEL)GLOBAL_PANEL;
    move_right(panel, &b);
    move_right(panel, &b);
    move_right(panel, &b);
    move_down(panel, &b);
    move_down(panel, &b);
    move_down(panel, &b);

    _print_block(&b);
    int i;
    BOOL ret;
    for(i = 0; i < 4; i++){
        ret = turn(panel, &b);
        printf("%c: [%d]: %s\n",type, i, human_bool(ret));
        _print_block(&b);
        _print_panel(panel);
        if(!ret) break;
    }
}

void test_turn_block_filled(char type){
    GLOBAL_PANEL[5][4] = FILLED;
    test_turn_block(type);
}


int main(int argc, const char* argv[]){
    // test_init_panel();
    // test_print_block();
    // each_type_do(test_move_left);
    // each_type_do(test_move_right);
    // each_type_do(test_move_down);
    // each_type_do(test_move_with_filled);

    // test_turn_block('T');
    // test_turn_block('O');
    // test_turn_block('I');
    // test_turn_block('L');
    // test_turn_block('J');
    // test_turn_block('S');
    // test_turn_block('Z');

    test_turn_block_filled('I');



    return 0;
}

// gcc -I ../utils ../utils/utils.c test.c tetris.c -o test.out && ./test.out
