#ifndef HS_COMM_H
#define HS_COMM_H

#define PATHNAME    "/etc/passwd"
#define PROJ_ID     'g'

#define DATASIZE    128
#define MSGBUFSIZE  (DATASIZE + sizeof(long))

struct msgbuf {
	long dest;
	long src;
	char data[DATASIZE];
};

#endif	/* HS_COMM_H */
