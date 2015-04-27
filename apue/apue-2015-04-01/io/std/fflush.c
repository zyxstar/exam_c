/**
 * 在大多数情况下，缓冲区的存在是好事儿,作用为：合并系统调用
 *
 *	无缓冲: stderr,需要立刻输出
 *
 *	行缓冲：换行时候刷新，满了的时候刷新，强制刷新（标准输出是这样的，因为涉及到终端设备）
 *
 *	全缓冲：满了的时候刷新，强制刷新（默认，只要不是终端设备）
 * */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;

	for(i = 0 ; i < 5; i++)
	{
		putchar('x');
		fflush(stdout);
		sleep(1);
	}
	
	printf("\n");

}






