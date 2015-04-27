#include <stdio.h>

#define add(A, B) ((A) + (B))
#define mul(A, B) ((A) * (B))

#define max(A, B) ({			    \
			typeof(A) aa = (A); \
			typeof(B) bb = (B); \
			aa > bb ? aa : bb;  \
		})

#define pri(A) do {printf("%d\n", A); printf("%c\n", A);} while (0)

inline int add(int a, int b)
{
	return a + b;
}

#define foo(A) #A
#define bar(A, B) A ## B
#define mysyscall(A, TYPE1, DATA1, TYPE2, DATA2) int sys_ ## A (TYPE1 DATA1, TYPE2 DATA2)

mysyscall(read, int, a, int, b)
{
	xxx;
	return x;
}

int main(void)
{
	int a, b, c;

	foo(12345);
	bar(1234, abc);

	if ()
		pri(3);
	else
		pri(4);

	a = 3, b = 7;
	c = max(a++, b++);

	printf("a = %d, b = %d, c = %d\n", a, b, c);

	return 0;
}
