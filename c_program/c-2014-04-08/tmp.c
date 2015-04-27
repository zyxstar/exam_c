int a;
int a[5];
int *a;
int a(int, int);

int *a[5];
int (*a)[5];
int *(*a)[5];
int *a(int, int);
int (*a)(int, int);
int *(*a)(int, int);
int *(*a)(int, int *);

int *(*a[5])(int, int *);

int a(int, int (*)(int));

int (*a(int, int (*)(int)))(int);
int (       *a(int, int (*)(int))        )(int);

typedef int func_t(int);
func_t *a(int, func_t *);
double *a(int, double *);

typedef int (*funcp_t)(int);
funcp_t a(int, funcp_t);

typedef int arr[4];
arr a;

struct data_st {
	int ind;
	char data[];
};

struct packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		char path[0];
		int ack;
		struct data_st data;
	};
};

struct packet_st a;
//a.xxx.ack;
a.ack;
