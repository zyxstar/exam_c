#ifndef HS_PROTOCOL_H
#define HS_PROTOCOL_H

#include <arpa/inet.h>

struct __attribute__ ((__packed__)) data_st {
	uint32_t ind;
	char data[0];
};

#define PADSIZE         (130 - 2)
#define TRANS_DATASIZE  (PADSIZE - 4)

struct __attribute__ ((__packed__)) packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		char name[0];
		char salt[0];
                char encrypt[0];
		char path[0];
		uint8_t ack;
		struct data_st data;
		char list[0];
		char pad[PADSIZE];
	};
};

#define PROTOCOL_MAJOR_LOGIN        1
#define PROTOCOL_MAJOR_DOWNLOAD     2
#define PROTOCOL_MAJOR_LIST         4
#define PROTOCOL_MAJOR_ERROR        50

#endif	/* HS_PROTOCOL_H */
