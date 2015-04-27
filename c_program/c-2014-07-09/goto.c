#include <stdio.h>

int bar(void)
{
	int ret;

	ret = op1();
	if (ret == -1) {
		goto err1;
	}

	ret = op3();
	if (ret == -1) {
		goto err3;
	}

	ret = op4();
	if (ret == -1) {
		goto err4;
	}

	ret = op5();
	if (ret == -1) {
		goto err5;
        }

	ret = op6();
	if (ret == -1) {
		goto err6;
        }












































	ret = op7();
	if () {
		goto err7;
	}








	return 0;


	close7();
err7:
	close6();
err6:
	close5();
err5:
	close4();
err4:
	close3();
err3:
	close1();
err1:
	return -1;
}

void foo(void)
{
	int i;

#if 1
	i = 0;
loop:
	printf("i = %d\n", i);
	i++;
	if (i < 10) {
		goto loop;
	}
#else
	for (i = 0; i < 10; i++) {
		printf("i = %d\n", i);
	}
#endif
}

int main(void)
{
	printf("hello");

	goto xxx;

	printf("nm");

xxx:
	printf(" xxx\n");

	return 0;
}
