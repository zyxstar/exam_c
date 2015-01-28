#include <stdio.h>

void my_lib_tunction();

int main(){
    my_lib_tunction();
    return 0;
}

// gcc -o tomato_main tomato_main.c -ltomato -L.

// export LD_LIBRARY_PATH=/home/zyx/Public/web_proj/exam_c/c_program:$LD_LIBRARY_PATH

// ldd tomato_main #查看依赖

// size tomato_main #查看段信息

// nm tomato_main #查看符号
// bss 非初始化数据段
