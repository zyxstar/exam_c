
struct data_st {
	int16_t ind;
	int8_t text[];
};

struct packet_st {
	uint8_t major;
	uint8_t minor;
	union {
		int8_t name[];
		int16_t ind;
		int8_t ack;
		struct data_st data;
	};
};

void foo(void)
{
	struct packet_st pkt;
	read(sd, pkt, sizeof(pkt));

	if (pkt.major == 1) {
		if (pkt.minor == 1) {
			pkt.name;
		}
	}
}
