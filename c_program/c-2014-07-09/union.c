#include <stdio.h>

struct data_st {
	uint32_t ind;
	char data[];
};

struct packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		char name[];
		char salt[];
		char encrypt[];
		uint8_t ack;
		struct data_st data;
	};
} xxxxxxxxxxxxxxxxx;

union {
	int a;
	int b;
	char str[9];
	double d;
} xxx;

int main(void)
{
	xxx.a = 0x303132;
	printf("%s\n", xxx.str);
	printf("sizeof(xxx) = %d\n", sizeof(xxx));

	return 0;
}
