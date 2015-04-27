#include <stdio.h>

#define add(A, B) ((A) + (B))
#define mul(A, B) ((A) * (B))
//#define min(A, B) ((A) < (B) ? (A) : (B))
#define min(A, B) ({				\
			typeof(A) xx = (A);	\
			typeof(B) yy = (B);	\
			xx < yy ? xx : yy; })

#define tmp(X) do {printf("%d ", X); printf("%c\n", X);} while (0)

#define temp(X) #X

#define foo(X, Y) X ## Y

int main(void)
{
	int a, b, c;

	b = 33, c = 44;

	//a = add(b, c) * 2;
	//a = mul(b, c + 2);
	a = min(b++, c++);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	int xx, yy, zz;
	xx = 5, yy = 8;
	zz = min(xx++, yy++);
	printf("xx = %d, yy = %d, zz = %d\n", xx,yy, zz);

	a = 'P';
	if (3 < 5)
		tmp(a);
	else
		printf("xxxxxxxxx\n");

	tmp(a);
#undef tmp
	tmp(a);

	temp(abcdefg);
	foo(abc, 12345);

	"hello "     "world!";
#define bar(X, Y) #X #Y
	bar(hello, world);

	return 0;
}
