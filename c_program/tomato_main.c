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

// cat /proc/cpuinfo 查看CPU的
// cat /proc/meminfo 查看内存
// cat /proc/swaps  查看swap分区信息
// vmstat 3 每三秒钟捕获一次。第一行数据不用看，没有价值，它仅反映开机以来的平均性能。从第二行开始，反映每三秒钟之内的系统性能指标
// free  可以看到总内存
