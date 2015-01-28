#include <stdlib.h>

char pear[40];
static double peach;
int mangc = 13;
static long melon = 2001;
const int r_data = 1;
const int r_data2;

extern int ex_data;

int main(){
    int i = 3, *ip;
    static j;
    static k = 3;
    ip = malloc(sizeof(i));
    pear[5] = i;
    peach = 2.0 * melon;
}

static void func(){}

// gcc nm_test.c -o nm_test.out
// nm nm_test.out
// objdump nm_test.out

// .bss 非初始化数据段(运行时所需要的BSS段的大小记录在目标文件中，但并不占据目标文件的任何空间)
//     B pear                # char pear[40];
//     B r_data2             # const int r_data2;
//     b peach               # static double peach;
//     b j.1789              # static j;
// .data 初始化数据段
//     D mangc               # int mangc = 13;
//     d melon               # static long melon = 2001;
//     d k.1780              # static k = 3;
// .rodata 只读数据区
//     R r_data              # const int r_data = 1;
// .text 代码区
//     T main                # int main()
//     t fun                 # static void func()
// UNDEF 未定义(定义的为T)
//     U malloc@@GLIBC_2.0   # ip = malloc(sizeof(i));
//

// #该符号的值是绝对的，在以后的链接过程中，不允许进行改，这样的符号值，常常出现在中断向量表中，例如用符号来表示各个中断向量函数在中断向量表中的位置。
// A __bss_start
// A _edata
// A _end

// #weak symbol
// W data_start
// w __gmon_start__
// w _Jv_RegisterClasses

// 局部变量 如i, ip 并不进入，它们在运行时创建
// extern int ex_data; 并不进入，它属于声明

// 数据段保存在目标文件中
// SS段不保存在目标文件中（除了记录BSS段在运行时所需的大小）
// 文本段最受优化措施影响的段
// 输出文件大小受调试状态下编译的影响，但段不受影响
