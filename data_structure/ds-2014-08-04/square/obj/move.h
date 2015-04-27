#ifndef HS_SQUARE_MOVE_H
#define HS_SQUARE_MOVE_H

#include "comm.h"

void init(void);
void init_little(void);

void move_left(void);
void move_right(void);
int move_down(void);
void roll(void);

void little2big(int arr[20][10]);

void clear_line(void);

#endif	/* HS_SQUARE_MOVE_H */
