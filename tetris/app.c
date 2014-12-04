#include <stdio.h>
#include <stdlib.h>
// #include "utils.h"
// #include "tetris.h"

#define W 20
#define H 20

int shape_num = 0;
int down_one = 0;
int move_left =0;
int move_right = 0;
int move_down =0;
int score_num = 0;
int down_init = 0;
int next_shape_num = 5;
int color_num = 44;
int press_pause = 1;

void init_frame(void )
{
    int i, j;
    int k, l;

    printf("\33[2J\033[1;1H");                          //每次都清屏

    for (i = 0; i < H + 5; i++)                     //每次都打印边框
        {
            for (j = 0; j < 10 + W; j++)
                {
                if (((j > 10 && j < W + 10) && i == 3)
                || ((j > 10 && j < W + 10) && i == H + 5 - 1)
                || (j == 10 + 1 && (i > 3 && i < H + 5 - 1))
                || (j == W + 10 - 1 && (i > 3 && i < H + 5 - 1))
                || (j == 22 && (i > 3 && i < H + 5 - 1)))
                {
                    printf("\033[45m  \033[0m");
                }
                    else
                {
                        printf("  ");
                }
        }
            printf("\n");
}
                                                                                                        //边框 分数 信息
        printf("\033[33m\033[%d;%dH @iceyang\n\033[0m",3,48);
        printf("\033[33;4m\033[%d;%dH   NEXT  \n\033[0m",5,48);
        printf("\033[33;4m\033[%d;%dH  score  \n\033[0m",11,48);
        printf("\033[31m\033[%d;%dH%d\n\033[0m",13,52,score_num);

        printf("\033[34m\033[%d;%dH 发炮: f  \n\033[0m",15,48);
        printf("\033[31m\033[%d;%dH 变形: w  \n\033[0m",16,48);
        printf("\033[31m\033[%d;%dH 向下: s  \n\033[0m",17,48);
        printf("\033[31m\033[%d;%dH 向左: a  \n\033[0m",18,48);
        printf("\033[31m\033[%d;%dH 向右: d  \n\033[0m",19,48);
        printf("\033[31m\033[%d;%dH 暂停: p  \n\033[0m",20,48);
        printf("\033[31m\033[%d;%dH 退出: q  \n\033[0m",21,48);

    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num + 1,shape[next_shape_num][0] + 3 + 4, shape[next_shape_num][1] + 25 + 17 );
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][2] + 3 + 4, shape[next_shape_num][3] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][4] + 3+ 4, shape[next_shape_num][5] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][6] + 3+ 4 , shape[next_shape_num][7] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][8] + 3 + 4, shape[next_shape_num][9] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][10] + 3+ 4 , shape[next_shape_num][11] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][12] + 3+ 4, shape[next_shape_num][13] + 25+ 17);
    //     printf("\033[%dm\033[%d;%dH \n\033[0m",color_num+ 1,shape[next_shape_num][14] + 3 + 4, shape[next_shape_num][15] + 25+ 17);

    //                                                                                         // 打印已经存入wall的，位置信息，并且随着 init 打印出来
    // for(k = 0; k < 20; k++)
    // {
    //     for(l = 0; l < 20; l++)
    //     {
    //         if(wall[k][l] == '#')
    //         printf("\033[43m\033[%d;%dH#\n\033[0m", k + 3, l + 25 );
    //     }
    // }
}



int main(int argc, const char* argv[]){

  init_frame();
  return 0;
}


// gcc -I ../utils ../utils/utils.c tetris.c view.c app.c -o app.out -DDEBUG && ./app.out
// gcc -I ../utils ../utils/utils.c tetris.c view.c app.c -o app.out && ./app.out
