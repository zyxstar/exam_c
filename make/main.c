#include <stdio.h>
#include "utils.h"
#include "a.h"
#include "b.h"
int main()
{
	int a=2;
	int b=3;
	add(a,b);
	sub(a,b);
    printf(VT_RED"good\n"VT_RESET);
	return 0;
}
