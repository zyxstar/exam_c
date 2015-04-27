int a;
int *a;
int a[4];
int a(int, double);

int *a[4];
int (*a)[4];
int *a(int, double);
int (*a)(int, double);

int *(*a)[4];
int *(*a[4])[5];
int (*(*a[4])[5])(int);
int (*(*(*a[4])[5])(int))[2];
int (   *  (*(*a[4])[5])  (int)     )[2];

void (*func(int, void (*)(int)))(int);
void (  *   func(int, void (*)(int))         )(int);
