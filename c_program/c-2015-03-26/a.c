#define data *(unsigned long *)0x3010
#define status *(unsigned long *)0x3014
#define cmd *(unsigned long *)0x3018

struct register {
	unsigned long data;
	unsigned long status;
	unsigned long cmd;
} *reg = (struct register *)0x3010;

void bar(void (*p)(void))
{
	data = 6;
	reg->data = 6;

	int a;
	int b;
	int c;
	int arr[9];
	struct abc {
		int a;
		int b;
		int c;
	};

	foo();
	p();
}
