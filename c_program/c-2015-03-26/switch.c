#include <stdio.h>
/*
void foo(int a)
{
	if (a == 1) {
		xxx;
	} else if (a == 3) {
		yyy;
	} else {
		zzz;
	}

	switch (a) {
	case 1:
		xxx;
		break;
	case 3:
		yyy;
		break;
	default:
		zzz;
		break;
	}
}
*/
void bar(int a)
{
	if (a == 5) {
		open("tmp", 0);
	}
	close(6);
}

int main(void)
{

}
