#ifndef HS_PROTOCOL_H
#define HS_PROTOCOL_H

#define PACKET_SIZE   1400
#define PAD_SIZE      (PACKET_SIZE - 2)

enum MAJOR {
	MA_LOGIN = 1,
	MA_MESSAGE = 2,
	MA_ERROR = 200,
};

struct message_st {
	uint32_t dest;
	uint32_t src;
	uint8_t message[0];
} __attribute__ ((__packed__));

struct packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		uint32_t id;
		uint8_t salt[0];
		uint8_t encrypt[0];
		uint8_t ack;
		struct message_st msg;
		uint8_t padded[PAD_SIZE];
	};
} __attribute__ ((__packed__));

#endif	/* HS_PROTOCOL_H */
