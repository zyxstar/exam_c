#include <stdio.h>

#if 0
int add(int a, int b)
{
	return a + b;
}
#else
#define add(A, B) ((A) + (B))
#endif

#define mul(A, B) ((A) * (B))

//#define min(A, B) ((A) < (B) ? (A) : (B))
#define min(A, B) ({ \
			int aa = (A); \
			int bb = (B); \
			aa < bb ? aa : bb; \
		})

#define pp(A, B) do {(A)++; (B)++;} while (0)

int main(void)
{
	int aa, bb, cc;

#if 65 - 65
	aa = 3;
#elif 3
	cc = 7;
#else
	bb = 4;
#endif

	cc = min(aa++, bb++);
#undef min
	cc = min(aa++, bb++);
	
	if (1)
		pp(aa, bb);
	else
		printf("xxx\n");

	printf("aa = %d, bb = %d, cc = %d\n", aa, bb, cc);

	return 0;
}
