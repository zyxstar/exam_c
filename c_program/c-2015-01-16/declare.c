int a;
int a[6];
int *a;
int a(int, double);

int *a[6];
int (*a)[6];
int *a(int, double);
int (*a)(int, double);

int (*a[6])(int, double);
int (*(*a)[6])(int, double);
int *(*(*a)[6])(int, double);
int *(   *(*a)[6]    )(int, double);
int (*a(int, double))[6];	/* int [6] * a(int, double); */

int (*f(int, int (*)(int)))(int);
int (   *f(int, int (*)(int)  )       )  (int);
//int (*)(int) f(int, int (*)(int));

typedef int (*funcp_t)(int);	/* int (*)(int) funcp_t */
funcp_t f(int, funcp_t);
double ff(int, double);

typedef int func_t(int);
func_t *f(int, func_t *);
