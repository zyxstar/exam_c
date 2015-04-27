#define NAND_BASE 0x30008040

#define NAND_COMMAND *(volatile unsigned long *)(NAND_BASE + 0x0)
#define NAND_STATUS  *(volatile unsigned long *)(NAND_BASE + 0x4)
#define NAND_ADDR    *(volatile unsigned long *)(NAND_BASE + 0x8)
#define NAND_DATA    *(volatile unsigned long *)(NAND_BASE + 0xc)

struct nand_register {
	unsigned long command;
	unsigned long status;
	unsigned long addr;
	unsigned long data;
};
volatile struct nand_register nand = (void *)NAND_BASE;

void foo(void)
{
	int a, b;
	NAND_COMMAND = 3;
	nand->command = 3;
}
