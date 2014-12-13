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


