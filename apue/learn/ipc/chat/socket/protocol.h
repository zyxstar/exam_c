#ifndef HS_CHAT_PROTOCOL_H
#define HS_CHAT_PROTOCOL_H

#include <arpa/inet.h>

#define PACKET_SIZE     1480
#define PADSIZE         (PACKET_SIZE - 2)
#define MSGSIZE         (PADSIZE - sizeof(uint32_t) * 2)
#define LISTNUM         (PADSIZE / sizeof(uint32_t))

struct __attribute__ ((__packed__)) msg_st {
	uint32_t dest;
	uint32_t src;
	uint8_t message[0];
};

struct __attribute__ ((__packed__)) packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		uint32_t id;
		uint8_t salt[0];
		uint8_t encrypt[0];
		uint8_t ack;
		struct msg_st msg;
		uint32_t list[0];
		uint8_t pad[PADSIZE];
	};
};

enum MAJOR {
	MAJOR_LOGIN = 1,
	MAJOR_MESSAGE,
	MAJOR_LIST,
	MAJOR_HEART = 10,
	MAJOR_MANAGE = 100,
	MAJOR_ERROR = 200,
};

#endif	/* HS_CHAT_PROTOCOL_H */
