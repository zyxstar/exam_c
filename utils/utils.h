#ifndef CONSOLE_H_INCLUEDE
#define CONSOLE_H_INCLUEDE

// printf("\033[1m\033[40;34mhello,world\033[0m\n" );
// printf(RED"RED FONT" BLUE "%s\n" NONE, "BLUE FONT" );
// 其中：
// /033[1m 设置高亮度
// /033[字背景颜色;字体颜色m字符串/033[0m

// 附录：vt100的控制符文档
// vt100可以实现终端上显示颜色，或者移动光标什么的，下面是网上流传的文档。
// =============颜色控制====================
// 格式: echo "33[字背景颜色;字体颜色m字符串33[0m"

// 例如:
// echo "33[41;36m something here 33[0m"
// 其中41的位置代表底色, 36的位置是代表字的颜色

// 那些ascii code 是对颜色调用的始末.
// 33[ ; m …… 33[0m

// 字背景颜色范围:40----49  // 字颜色:30-----------39
// 40:黑                   // 30:黑
// 41:深红                 // 31:红
// 42:绿                   // 32:绿
// 43:黄色                 // 33:黄
// 44:蓝色                 // 34:蓝色
// 45:紫色                 // 35:紫色
// 46:深绿                 // 36:深绿
// 47:白色                 // 37:白色

// ============ANSI控制码的说明 ===============
// 33[0m 关闭所有属性
// 33[1m 设置高亮度
// 33[4m 下划线
// 33[5m 闪烁
// 33[7m 反显
// 33[8m 消隐
// 33[30m -- 33[37m 设置前景色
// 33[40m -- 33[47m 设置背景色
// 33[nA 光标上移n行
// 33[nB 光标下移n行
// 33[nC 光标右移n行
// 33[nD 光标左移n行
// 33[y;xH设置光标位置
// 33[2J 清屏
// 33[K 清除从光标到行尾的内容
// 33[s 保存光标位置
// 33[u 恢复光标位置
// 33[?25l 隐藏光标
// 33[?25h 显示光标

#define VT_RESET                "\033[0m"
#define VT_LIGHT                "\033[1m"
#define VT_DEEP                 "\033[2m"
#define VT_UNDER                "\033[4m"
#define VT_REVERSE              "\033[7m"
#define VT_HIDE                 "\033[8m"


#define VT_BLACK                "\033[30m"
#define VT_RED                  "\033[31m"
#define VT_GREEN                "\033[32m"
#define VT_YELLOW               "\033[33m"
#define VT_BLUE                 "\033[34m"
#define VT_PURPLE               "\033[35m"
#define VT_CYAN                 "\033[36m"
#define VT_GRAY                 "\033[37m"
#define VT_BLACK_LIGHT          "\033[1;38m"

#define VT_BG_BLACK             "\033[40m"
#define VT_BG_RED               "\033[41m"
#define VT_BG_GREEN             "\033[42m"
#define VT_BG_YELLOW            "\033[43m"
#define VT_BG_BLUE              "\033[44m"
#define VT_BG_PURPLE            "\033[45m"
#define VT_BG_CYAN              "\033[46m"
#define VT_BG_WHITE             "\033[47m"
#define VT_BG_NONE              "\033[49m"

#define VT_HIED_CUR             "\033[?25l"
#define VT_SHOW_CUR             "\033[?25h"


#ifdef DEBUG
#define DEBUG_WRITE(arg) debug_write arg
#else
#define DEBUG_WRITE(arg)
#endif

void debug_write(char *format, ...);

#define SNAP_INT(arg) fprintf(stderr, VT_RESET "\033[35m[" #arg "] %d\n"VT_RESET, arg)
#define SNAP_CHAR(arg) fprintf(stderr, VT_RESET "\033[35m[" #arg "] %c\n"VT_RESET, arg)
#define SNAP_FLOAT(arg) fprintf(stderr, VT_RESET "\033[35m[" #arg "] %f\n"VT_RESET, arg)
#define SNAP_STRING(arg) fprintf(stderr, VT_RESET "\033[35m[" #arg "] %s\n"VT_RESET, arg)
#define SNAP_POINTER(arg) fprintf(stderr, VT_RESET "\033[35m[" #arg "] %p\n"VT_RESET, arg)


void printf_correct(char *format, ...);
void printf_error(char *format, ...);
void printf_info(char *format, ...);


typedef enum{
    FALSE,
    TRUE
} BOOL;

const char* human_bool(BOOL val);





struct{
    int interval;
    int const_interval;
    char callee_name[256];
    void(*callee_fn)();
} GLOBAL_SIMPLE_TIMER;

#define timer_new(arg1, arg2) \
        _timer_set_callee_name(#arg2);\
        _timer_set((arg1), (arg2)) \

#define timer_interval() GLOBAL_SIMPLE_TIMER.interval
#define timer_callee_name() GLOBAL_SIMPLE_TIMER.callee_name

void _timer_set_callee_name(char *source);
void _timer_set(int interval, void(*callee_fn)());

void timer_start();
void timer_stop();





#endif /*CONSOLE_H_INCLUEDE*/
