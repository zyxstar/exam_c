#ifndef HS_DB_H
#define HS_DB_H

#include <arpa/inet.h>

struct db_data_st {
	uint32_t id;
	struct sockaddr_in addr;
	/* last_time */
	/* online */
};

typedef void DB;

DB *db_creat(void);

void db_destroy(DB *);

int db_insert(DB *, struct db_data_st *);

void db_delet(DB *, uint32_t id);

struct db_data_st *db_search(DB *, uint32_t id);

#endif	/* HS_DB_H */
