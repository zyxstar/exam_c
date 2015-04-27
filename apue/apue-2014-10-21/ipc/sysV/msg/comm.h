#ifndef HS_COMM_H
#define HS_COMM_H

#define PATH       "/home/hsienmu"
#define PROJ_ID    'E'

#define TEXT_SIZE  256

struct msgbuf_st {
	long dest;
	char text[TEXT_SIZE];
};

#endif	/* HS_COMM_H */
