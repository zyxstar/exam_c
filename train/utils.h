#ifndef CONSOLE_H_INCLUEDE
#define CONSOLE_H_INCLUEDE


#define COLOR_NONE       "\033[0m"
#define BLACK            "\033[0;30m"
#define DARY_GRAY        "\033[1;30m"
#define RED              "\033[0;32;31m"
#define LIGHT_RED        "\033[1;31m"
#define GREEN            "\033[0;32;32m"
#define LIGHT_GREEN      "\033[1;32m"
#define BROWN            "\033[0;33m"
#define YELLOW           "\033[1;33m"
#define BLUE             "\033[0;32;34m"
#define LIGHT_BLUE       "\033[1;34m"
#define PURPLE           "\033[0;35m"
#define LIGHT_PURPLE     "\033[1;35m"
#define CYAN             "\033[0;36m"
#define LIGHT_CYAN       "\033[1;36m"
#define LIGHT_GRAY       "\033[0;37m"
#define WHITE            "\033[1;37m"

#define BG_BLACK         "\033[40m"
#define BG_RED           "\033[41m"
#define BG_GREEN         "\033[42m"
#define BG_YELLOW        "\033[43m"
#define BG_BLUE          "\033[44m"
#define BG_PURPLE        "\033[45m"
#define BG_LIGHT_GREEN   "\033[46m"
#define BG_WHITE         "\033[47m"
#define BG_NONE          "\033[49m"


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

//  那些ascii code 是对颜色调用的始末.
// 33[ ; m …… 33[0m


// 字背景颜色范围:40----49
// 40:黑
// 41:深红
// 42:绿
// 43:黄色
// 44:蓝色
// 45:紫色
// 46:深绿
// 47:白色

//  字颜色:30-----------39
// 30:黑
// 31:红
// 32:绿
// 33:黄
// 34:蓝色
// 35:紫色
// 36:深绿
// 37:白色

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





#ifdef DEBUG
#define DEBUG_WRITE(arg) debug_write arg
#else
#define DEBUG_WRITE(arg)
#endif

void debug_write(char *format, ...);

#define SNAP_INT(arg) fprintf(stderr, LIGHT_BLUE "[" #arg "] %d\n"COLOR_NONE, arg)
#define SNAP_CHAR(arg) fprintf(stderr, LIGHT_BLUE "[" #arg "] %c\n"COLOR_NONE, arg)
#define SNAP_FLOAT(arg) fprintf(stderr, LIGHT_BLUE "[" #arg "] %f\n"COLOR_NONE, arg)
#define SNAP_STRING(arg) fprintf(stderr, LIGHT_BLUE "[" #arg "] %s\n"COLOR_NONE, arg)
#define SNAP_POINTER(arg) fprintf(stderr, LIGHT_BLUE "[" #arg "] %p\n"COLOR_NONE, arg)


void printf_correct(char *format, ...);
void printf_error(char *format, ...);
void printf_info(char *format, ...);


typedef enum{
    FALSE,
    TRUE
} BOOL;

const char* human_bool(BOOL val);






#endif /*CONSOLE_H_INCLUEDE*/
