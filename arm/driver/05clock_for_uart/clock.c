#include <clock.h>
#include <common.h>

void clock_for_uart(void)
{
	#define CLK_DIV_PERIL0 (*(volatile unsigned int *)(0x10030000 + 0xC550))
	printf("LK_DIV_PERIL0 = %x\n", CLK_DIV_PERIL0);
	//LK_DIV_PERIL0 = 0x77777
	#define CLK_SRC_PERIL0  (*(volatile unsigned int *)(0x10030000+ 0xC250))
	printf("CLK_SRC_PERIL0 = %x\n", CLK_SRC_PERIL0);
	//CLK_SRC_PERIL0 = 0x66666
	#define CLK_SRC_TOP1 (*(volatile unsigned int *)(0x10030000 + 0xC214))
	printf("CLK_SRC_TOP1 = %x\n", CLK_SRC_TOP1);	
	//CLK_SRC_TOP1 = 0x1111000	
	#define CLK_SRC_DMC (*(volatile unsigned int *)(0x10040000 + 0x0200))
	printf("CLK_SRC_DMC = %x\n", CLK_SRC_DMC);
	//CLK_SRC_DMC = 0x11000
	#define MPLL_CON0 (*(volatile unsigned int *)(0x10040000 + 0x0108))
	printf("MPLL_CON0 = %x\n", MPLL_CON0);
	//MPLL_CON0 = a0640300
	//m = 100
	//p = 3
	//s = 0
	//fout = m * in / P / 2^s = 100 * 24M / 3 / 1
	//fout = 800M
}





