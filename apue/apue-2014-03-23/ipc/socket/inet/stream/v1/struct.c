#include <stdio.h>

struct __attribute__ ((__packed__)) bar {
	int a;
	char c;
};

struct foo {
	struct bar tmp;
	int a;
	char c;
	double d;
	char x;
} __attribute__ ((__packed__));

int main(void)
{
	printf("%d\n", sizeof(struct foo));

	return 0;
}

#ifdef GCC_XXX
struct foo {
	int a;
} __attribute__ ((__packed__));
#elif defined ICC_XXX
struct foo {
        int a;
} xxxxxxxxxxxxxxxxxx;
#endif
