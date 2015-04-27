int a;
int a[4];
int *a;
int a(int, double);

int *a[4];			/* int * [4] a; */
int (*a)[4];			/* int [4] *a; */
int *a(int, double);		/* int * (int, double) a; */
int (*a)(int, double);		/* int (int, double) * a; */

int (*a[4])(int, double);       /* int (int, double) * [4] a; */
int (*(*a)[4])(int, double);	/* int (int, double) * [4] * a; */
int *(*(*a)[4])(int, double);	/* int* (int, double) * [4] * a; */
int (*(*a)(int, double))[4];	/* int [4] * (int, double) * a; */

void (*a(int, void (*)(int)))(int);
/* a 是个函数，两个参数，第一个是int，第二个是函数指针void (*)(int)，返回函数指针void (*)(int) */

void (*a(int, void (*)(int)))(int);

typedef void (*funcp)(int);
funcp a(int, funcp);

typedef void func(int);
func *a(int, func *);
