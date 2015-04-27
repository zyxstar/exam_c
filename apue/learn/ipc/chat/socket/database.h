#ifndef HS_CHAT_DATABASE_H
#define HS_CHAT_DATABASE_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <time.h>

extern void *server_online_db;

struct database_record_st {
	uint32_t id;
	struct sockaddr_in addr;
	time_t last;
	int online;
};

int database_init(void);

void database_destroy(void);

int database_insert(const struct database_record_st *);

//database_delet();

struct database_record_st *database_find(uint32_t id);

void database_update(uint32_t id);

int database_getlist(uint32_t list[], int num);

#endif	/* HS_CHAT_DATABASE_H */
