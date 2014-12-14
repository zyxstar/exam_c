memmove 更安全的 copy 防止自己覆盖自己


free(NULL)是可以的，不会报错

条件注释，有效规避多行注释不能嵌套问题
#if 0

#else

#endif




1 != scanf("%d", &tmp);//出问题了


int arr[5];
arr+1 前进1 
&arr+1 前进5


如果 realloc 防止数据

指针数组 的malloc或realloc时，需要注意再次分配不成功时，会丢失 数组中 每个指针指向部分丢失






all: main
main: main.o chart.o
clean
    rm -rf *.o main





size
capacity

memset




NULL == (void*)0



返回所有符合条件
  定义子函数 内部static
  外部函数多次调用，直到全部找到，子函数内部static一直增加内容
  子函数定义的 static 作为外函数的 二级指针 参数




int find(DARR head, void *key, cmp, void **finddatas)
外部需要 free


最小指针模型
const char * const * const p = n

看const修饰 p or *p

线性表 宏


句柄 的改变 一般使用二级指针 形参改实参的值
（一般不会改变）





#define ARR_SIZE(arr) sizeof(arr) / sizeof(*arr)


   struct stu s = {};



