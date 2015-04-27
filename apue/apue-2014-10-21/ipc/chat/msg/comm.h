#ifndef HS_COMM_H
#define HS_COMM_H

#define PATH        "/etc/passwd"
#define PROJ_ID     'C'

#define TEXT_SIZE   1024

struct __attribute__ ((__packed__)) msgbuf_st {
	long dest;
	long src;
	char text[TEXT_SIZE];
};

#endif	/* HS_COMM_H */
